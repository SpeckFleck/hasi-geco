// -*- coding: utf-8; -*-
/*!
 * 
 * \file mcchd_wl.cpp
 * \brief Program frontend for running wang landau hard sphere simulations
 * 
 * For usage info execute:
 *  mcchd_wl --help
 * 
 * \author Johannes Knauf
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <cstdlib>

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include <mocasinns/random/boost_random.hpp>
#include <mocasinns/histograms/histocrete.hpp>
#include <mocasinns/wang_landau.hpp>
#include <HardDiscs.hpp>
#include <CollisionFunctor_SingularDefects.hpp>
#include <CollisionFunctor_NodalSurfaces.hpp>
#include <CollisionFunctor_SimpleGeometries.hpp>

namespace boost_po = boost::program_options;
namespace boost_fs = boost::filesystem;

#ifndef __MCCHD_VERSION
#define __MCCHD_VERSION "_unspecified version_"
#endif

#ifndef CONTAINER_NAME
#define CONTAINER_NAME Bulk
#endif

// double layering of definitions is necessary because of c preprocessor replacement rules
#define PASTER(x,y) x ## _ ## y
#define EVALUATOR(x,y) PASTER(x,y)
#define CONTAINER_TYPE EVALUATOR(mcchd::CF, CONTAINER_NAME)


typedef uint64_t signal_flag_t;
typedef mcchd::disc_id_type energy_type;
typedef Mocasinns::Random::Boost_MT19937 RngType;
typedef CONTAINER_TYPE ContainerType;
typedef Mocasinns::Histograms::Histocrete<energy_type, long unsigned int> IncidenceHistogramType;
typedef Mocasinns::Histograms::Histocrete<energy_type, double> HistogramType;
typedef mcchd::HardDiscs<ContainerType> ConfigurationType;
typedef mcchd::Step<ConfigurationType> StepType;
typedef Mocasinns::Simulation<ConfigurationType, RngType> ParentSimulationType;
typedef Mocasinns::WangLandau<ConfigurationType, StepType, energy_type, Mocasinns::Histograms::Histocrete, RngType> SimulationType;

static std::string output_directory;

void init_logging()
{
  boost::log::add_common_attributes();
  boost::log::add_console_log(std::clog, 
			      boost::log::keywords::format = boost::log::expressions::stream
			      << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
			      << " [" << boost::log::expressions::attr< unsigned int >("LineID")
			      << "] <" << boost::log::expressions::attr< boost::log::trivial::severity_level >("Severity")
			      << "> " << boost::log::expressions::message);
  
  boost::log::add_file_log (boost::log::keywords::file_name = (output_directory + std::string("/protocol.log")).c_str(), 
			    boost::log::keywords::auto_flush = true,
			    boost::log::keywords::format = boost::log::expressions::stream
			    << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
			    << " [" << boost::log::expressions::attr< unsigned int >("LineID")
			    << "] <" << boost::log::expressions::attr< boost::log::trivial::severity_level >("Severity")
			    << "> " << boost::log::expressions::message);

  boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
  BOOST_LOG_TRIVIAL(info) << "Logging facilities successfully initialized.";
}

void write_dos_to_file(std::string output_filename, HistogramType& entropy_estimation)
{
  if (boost_fs::exists(output_filename))
    {
      BOOST_LOG_TRIVIAL(error) << "File " << output_filename << " already exists. Only one user request per second at max please.";
    }
  else
    {
      std::ofstream *output_fstream = new std::ofstream;
      output_fstream->open(output_filename.c_str());
      
      if (!(*output_fstream)) // Is output_fstream OK?
	{
	  throw 5;
	}
      
      (*output_fstream) << "# E: Energy" << std::endl;
      (*output_fstream) << "# S: Entropy" << std::endl;
      (*output_fstream) << "# E S" << std::endl;
      
      (*output_fstream) << std::scientific << std::setprecision(std::numeric_limits<double>::digits10 + 1);
      (*output_fstream) << entropy_estimation << std::endl;
      delete output_fstream;
      BOOST_LOG_TRIVIAL(info) << "Wrote entropy estimate to " << output_filename;
    }
}

void handle_sig_usr1(ParentSimulationType* parent_simulation)
{
  BOOST_LOG_TRIVIAL(debug) << "Caught SIGUSR1. Writing a snapshot of the entropy estimation";
  SimulationType* wang_landau_simulation = static_cast<SimulationType*> (parent_simulation);
  HistogramType entropy_estimation = wang_landau_simulation->get_log_density_of_states();
  // normalize histogram before output
  entropy_estimation.shift_bin_zero(entropy_estimation.min_x_value());

  const time_t current_time = time (NULL);
  char world_time[16];
  strftime (world_time, 16, "%Y%m%d-%H%M%S", gmtime(&current_time));
  std::string output_file = output_directory + "/intermediate_entropy," + world_time;
  write_dos_to_file(output_file, entropy_estimation);
}

void handle_sig_usr2(ParentSimulationType* parent_simulation)
{
  BOOST_LOG_TRIVIAL(debug) << "Caught SIGUSR2. Manually clearing flatness counter.";
  SimulationType* wang_landau_simulation = static_cast<SimulationType*> (parent_simulation);
  IncidenceHistogramType incidence_counter = wang_landau_simulation->get_incidence_counter();

  incidence_counter.set_all_y_values(0);
  wang_landau_simulation->set_incidence_counter(incidence_counter);
}

void handle_sig_term(ParentSimulationType* parent_simulation)
{
  BOOST_LOG_TRIVIAL(debug) << "Caught SIGTERM.";
  BOOST_LOG_TRIVIAL(debug) << "No special handling for SIGTERM yet. Calling SIGUSR1 handler for writing a snapshot before exiting.";
  handle_sig_usr1(parent_simulation);
  exit(2);
}

void sweep_handler(ParentSimulationType* parent_simulation)
{
  SimulationType* wang_landau_simulation = static_cast<SimulationType*> (parent_simulation);

  BOOST_LOG_TRIVIAL(info) << "Sweep completed with \tt= " << wang_landau_simulation->get_config_space()->get_simulation_time() 
			  << " \tm= " << wang_landau_simulation->get_modification_factor_current()
			  << " \tf= " << wang_landau_simulation->get_incidence_counter().flatness();
}

void modfac_handler(ParentSimulationType* parent_simulation)
{
  SimulationType* wang_landau_simulation = static_cast<SimulationType*> (parent_simulation);
  const double current_modification_factor = wang_landau_simulation->get_modification_factor_current();
  HistogramType log_density_of_states = wang_landau_simulation->get_log_density_of_states();

  // normalize histogram before output
  log_density_of_states.shift_bin_zero(log_density_of_states.min_x_value());

  const time_t current_time = time (NULL);
  char world_time[16];
  strftime (world_time, 16, "%Y%m%d-%H%M%S", gmtime(&current_time));
  std::string output_file = output_directory + "/modfac_entropy_dump," + world_time + ",mod=" + (boost::format("%e") % current_modification_factor).str();

  write_dos_to_file(output_file, log_density_of_states);
}

// declaration of the main simulation routine -- defined below
void run_simulation(boost_po::variables_map&, std::string&);


int main(int argc, char* argv[])
{
  try 
    {
      boost_po::options_description option_desc("Available options");
      option_desc.add_options()
        ("help,h", "Prints this message.")
        ("version,v", "Prints version information.")
        ("width,w,x", boost_po::value<double>()->default_value(10.), "Width of the Box - x coordinate.")
        ("height,h,y", boost_po::value<double>()->default_value(10.), "Height of the Box - y coordinate.")
        ("depth,d,z", boost_po::value<double>()->default_value(10.), "Depth of the Box - z coordinate.")
        ("seed,S", boost_po::value<uint32_t>()->default_value(1), "Seed of the Random number generator.")
        ("flatness,f", boost_po::value<double>()->default_value(0.8), "Flatness criterion, minimum sampling frequency of an energy in relation to mean frequency.")
        ("mod_final,m", boost_po::value<double>()->default_value(1e-2), "Final modification factor.")
        ("mod_start,s", boost_po::value<double>()->default_value(1.0), "Modification factor at beginning of simulation.")
        ("mod_multi,M", boost_po::value<double>()->default_value(0.5), "Modification factor multiplier - gets multiplied whenever flatness is reached.")
        ("energy_cutoff_lower,e", boost_po::value<uint64_t>(), "Set lower energy limit E_min. No lower limit, if parameter is missing.")
        ("energy_cutoff_upper,E", boost_po::value<uint64_t>(), "Set upper energy limit E_max. No upper limit, if parameter is missing.")
        ("output_directory,o", boost_po::value<std::string>(), "Directory for the output of results, progress reports etc.")
        ("sweep_steps,N", boost_po::value<double>()->default_value(1e4), "How many steps between 2 flatness checks and corresponding status reports etc.")
	("logdos_file,i", boost_po::value<std::string>(), "Input CSV file containing the initial entropy estimation.")
        ;
      
      boost_po::variables_map option_arguments;
      boost_po::store (boost_po::parse_command_line (argc, argv, option_desc), option_arguments);
      boost_po::notify (option_arguments);
      
      if (option_arguments.count("help"))
        {
	  std::cerr << "Usage: mcchd_wl [options]" << std::endl;
	  std::cerr << option_desc;
          return 0;
        }
      else if (option_arguments.count("version"))
	{
	  std::cerr << "This is mcchd_wl version " << __MCCHD_VERSION << std::endl;
	  std::cerr << "Copyleft 2013 Johannes F Knauf." << std::endl;
	  return 0;
	}
      
      std::string program_name = std::string(argv[0]);

      run_simulation(option_arguments, program_name);
    }
  catch (std::exception &exceptionX)
    {
      std::cout << exceptionX.what() << std::endl;
      return 1;
    }

  return 0;
}



void run_simulation(boost_po::variables_map& option_arguments, std::string& program_name)
{
  BOOST_LOG_TRIVIAL(debug) << "Entered run_simulation.";

  // read options
  const double x_max = option_arguments["width"].as<double>();
  const double y_max = option_arguments["height"].as<double>();
  const double z_max = option_arguments["depth"].as<double>();
  const uint32_t seed = option_arguments["seed"].as<uint32_t>();
  const double flatness = option_arguments["flatness"].as<double>();
  const double mod_final = option_arguments["mod_final"].as<double>();
  const double mod_start = option_arguments["mod_start"].as<double>();
  const double mod_multi = option_arguments["mod_multi"].as<double>();
  const double sweep_steps = option_arguments["sweep_steps"].as<double>();

  bool energy_cutoff_upper_use = false;
  uint64_t energy_cutoff_upper = 0;
  if (option_arguments.count("energy_cutoff_upper"))
    {
      energy_cutoff_upper_use = true;
      energy_cutoff_upper = option_arguments["energy_cutoff_upper"].as<uint64_t>();
    }

  bool energy_cutoff_lower_use = false;
  uint64_t energy_cutoff_lower = 0;
  if (option_arguments.count("energy_cutoff_lower"))
    {
      energy_cutoff_lower_use = true;
      energy_cutoff_lower = option_arguments["energy_cutoff_lower"].as<uint64_t>();
    }

  BOOST_LOG_TRIVIAL(debug) << "Finished reading simulation options.";

  boost::format output_directory_formatter;

  if (option_arguments.count("output_directory"))
    {
      output_directory = option_arguments["output_directory"].as<std::string>();
    }
  else
    {
      output_directory = (boost::format("%s,x%.1e,y%.1e,z%.1e,S%d,f%.1e,m%.1e,s%.1e,M%.1e,e%d,E%d,N%.1e")
			  % program_name.c_str()
			  % x_max
			  % y_max
			  % z_max
			  % seed
			  % flatness
			  % mod_final
			  % mod_start
			  % mod_multi
			  % energy_cutoff_lower
			  % energy_cutoff_upper
			  % sweep_steps).str();
    }
  output_directory_formatter = boost::format(output_directory + "_%d");
  uint64_t trial_number = 0;
  output_directory = (output_directory_formatter % trial_number).str();
  while(boost_fs::exists(output_directory.c_str()))
    {
      BOOST_LOG_TRIVIAL(debug) << "Proposed output directory " << output_directory.c_str() << " already exists. Trying next suffix number.";
      trial_number += 1;
      output_directory = (output_directory_formatter % trial_number).str();
    }
  boost_fs::create_directory(output_directory.c_str());
  BOOST_LOG_TRIVIAL(debug) << "Created output directory " << output_directory.c_str();

  init_logging();

  // create simulation objects
  mcchd::coordinate_type extents = {{x_max, y_max, z_max}};

  SimulationType::Parameters wang_landau_parameters;
  wang_landau_parameters.modification_factor_initial = mod_start;
  wang_landau_parameters.modification_factor_final = mod_final;
  wang_landau_parameters.modification_factor_multiplier = mod_multi;
  wang_landau_parameters.flatness = flatness;
  wang_landau_parameters.sweep_steps = sweep_steps;
  wang_landau_parameters.use_energy_cutoff_upper = energy_cutoff_upper_use;
  wang_landau_parameters.energy_cutoff_upper = energy_cutoff_upper;
  wang_landau_parameters.use_energy_cutoff_lower = energy_cutoff_lower_use;
  wang_landau_parameters.energy_cutoff_lower = energy_cutoff_lower;

  ConfigurationType* hard_sphere_configuration = new ConfigurationType(extents);
  SimulationType* wang_landau_simulation = new SimulationType(wang_landau_parameters, hard_sphere_configuration);;

  wang_landau_simulation->set_random_seed(seed);
  
  // attach watchers
  wang_landau_simulation->signal_handler_sigusr1.connect(handle_sig_usr1);
  wang_landau_simulation->signal_handler_sigusr2.connect(handle_sig_usr2);
  wang_landau_simulation->signal_handler_sigterm.connect(handle_sig_term);
  wang_landau_simulation->signal_handler_sweep.connect(sweep_handler);
  wang_landau_simulation->signal_handler_modfac_change.connect(modfac_handler);

  HistogramType entropy_estimation;
  if (option_arguments.count("logdos_file"))
    {
      std::string filename = option_arguments["logdos_file"].as<std::string>();
      BOOST_LOG_TRIVIAL(info) << "Log DOS file option present. Loading file " << filename.c_str();
      entropy_estimation.load_csv(filename.c_str());
      wang_landau_simulation->set_log_density_of_states(entropy_estimation);
    }

  // run
  wang_landau_simulation->do_wang_landau_simulation();

  delete hard_sphere_configuration;
  delete wang_landau_simulation;
}
