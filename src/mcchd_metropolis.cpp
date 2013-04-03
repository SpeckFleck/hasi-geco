// -*- coding: utf-8; -*-
/*!
 * 
 * \file mcchd_metropolis.cpp
 * \brief Program frontend for running metropolis hard sphere simulations
 * 
 * For usage info execute:
 *  mcchd_metropolis --help
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

#include <mocasinns/histograms/histocrete.hpp>
#include <mocasinns/random/boost_random.hpp>
#include <mocasinns/metropolis.hpp>
#include <HardDiscs.hpp>
#include <CollisionFunctor_SingularDefects.hpp>
#include <CollisionFunctor_NodalSurfaces.hpp>
#include <CollisionFunctor_SimpleGeometries.hpp>

namespace boost_po = boost::program_options;
namespace boost_fs = boost::filesystem;

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
typedef Mocasinns::Histograms::Histocrete<energy_type, long long int> IncidenceHistogramType;
typedef Mocasinns::Histograms::Histocrete<energy_type, double> HistogramType;
typedef mcchd::HardDiscs<ContainerType> ConfigurationType;
typedef mcchd::Step<ConfigurationType> StepType;
typedef Mocasinns::Simulation<ConfigurationType, RngType> ParentSimulationType;
typedef Mocasinns::Metropolis<ConfigurationType, StepType, RngType> SimulationType;

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

void append_value_to_file(std::string output_file, energy_type energy)
{
  std::ofstream *output_fstream = new std::ofstream;
  output_fstream->open(output_file.c_str(), std::fstream::app);
  
  if (!(*output_fstream)) // Is output_fstream OK?
    {
      throw 5;
    }
  
  (*output_fstream) << energy << std::endl;
  delete output_fstream;
}

void handle_sig_usr1(ParentSimulationType* parent_simulation)
{
  BOOST_LOG_TRIVIAL(debug) << "Caught SIGUSR1. No action defined.";
}

void handle_sig_usr2(ParentSimulationType* parent_simulation)
{
  BOOST_LOG_TRIVIAL(debug) << "Caught SIGUSR2. No action defined.";
}

void handle_sig_term(ParentSimulationType* parent_simulation)
{
  BOOST_LOG_TRIVIAL(debug) << "Caught SIGTERM.";
  BOOST_LOG_TRIVIAL(debug) << "No special handling for SIGTERM yet. Calling SIGUSR1 handler for writing a snapshot before exiting.";
  handle_sig_usr1(parent_simulation);
  exit(2);
}

void measurement_handler(ParentSimulationType* parent_simulation)
{
  SimulationType* metropolis_simulation = static_cast<SimulationType*> (parent_simulation);
  const energy_type current_energy = metropolis_simulation->get_config_space()->energy();

  std::string output_file = output_directory + "/measurements.out";

  append_value_to_file(output_file, current_energy);
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
        ("width,w,x", boost_po::value<double>()->default_value(10.), "Width of the Box - x coordinate.")
        ("height,h,y", boost_po::value<double>()->default_value(10.), "Height of the Box - y coordinate.")
        ("depth,d,z", boost_po::value<double>()->default_value(10.), "Depth of the Box - z coordinate.")
        ("seed,S", boost_po::value<uint32_t>()->default_value(1), "Seed of the Random number generator.")
        ("relaxation_steps,r", boost_po::value<uint32_t>()->default_value(1000), "Number of steps before beginning measurement.")
        ("num_measurements,n", boost_po::value<uint32_t>()->default_value(1000), "How many samples should be taken.")
        ("beta,b", boost_po::value<double>()->default_value(1.0), "Inverse temperature beta.")
        ("output_directory,o", boost_po::value<std::string>(), "Directory for the output of results, progress reports etc.")
        ("steps_between_measurements,N", boost_po::value<uint32_t>()->default_value(100), "How many steps between 2 measurements.")
        ;
      
      boost_po::variables_map option_arguments;
      boost_po::store (boost_po::parse_command_line (argc, argv, option_desc), option_arguments);
      boost_po::notify (option_arguments);
      
      if (option_arguments.count("help"))
        {
	  std::cerr << "Usage: mcchd_metropolis [options]" << std::endl;
	  std::cerr << option_desc;
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
  const uint32_t relaxation_steps = option_arguments["relaxation_steps"].as<uint32_t>();
  const uint32_t num_measurements = option_arguments["num_measurements"].as<uint32_t>();
  const uint32_t steps_between_measurements = option_arguments["steps_between_measurements"].as<uint32_t>();
  const double beta = option_arguments["beta"].as<double>();

  BOOST_LOG_TRIVIAL(debug) << "Finished reading simulation options.";

  boost::format output_directory_formatter;

  if (option_arguments.count("output_directory"))
    {
      output_directory = option_arguments["output_directory"].as<std::string>();
    }
  else
    {
      output_directory = (boost::format("%s,x%.1e,y%.1e,z%.1e,S%d,b%.1e,r%.1e,n%.1e,N%.1e")
			  % program_name.c_str()
			  % x_max
			  % y_max
			  % z_max
			  % seed
			  % beta
			  % relaxation_steps
			  % num_measurements
			  % steps_between_measurements).str();
    }
  output_directory_formatter = boost::format(output_directory + "_%d");
  uint64_t trial_number = 0;
  output_directory = (output_directory_formatter % trial_number).str();
  while(boost_fs::exists(output_directory.c_str()))
    {
      BOOST_LOG_TRIVIAL(debug) << "Proposed output directory " << output_directory.c_str() << " already exists. Trying next suffix number." << std::endl;
      trial_number += 1;
      output_directory = (output_directory_formatter % trial_number).str();
    }
  boost_fs::create_directory(output_directory.c_str());
  BOOST_LOG_TRIVIAL(debug) << "Created output directory " << output_directory.c_str() << std::endl;

  init_logging();

  // create simulation objects
  mcchd::coordinate_type extents = {{x_max, y_max, z_max}};

  SimulationType::Parameters metropolis_parameters;
  metropolis_parameters.relaxation_steps = relaxation_steps;
  metropolis_parameters.measurement_number = num_measurements;
  metropolis_parameters.steps_between_measurement = steps_between_measurements;

  ConfigurationType* hard_sphere_configuration = new ConfigurationType(extents);
  SimulationType* metropolis_simulation = new SimulationType(metropolis_parameters, hard_sphere_configuration);

  metropolis_simulation->set_random_seed(seed);
  
  // attach watchers
  metropolis_simulation->signal_handler_sigusr1.connect(handle_sig_usr1);
  metropolis_simulation->signal_handler_sigusr2.connect(handle_sig_usr2);
  metropolis_simulation->signal_handler_sigterm.connect(handle_sig_term);

  
  BOOST_LOG_TRIVIAL(info) << "Making " << relaxation_steps << " relaxation steps.";
  metropolis_simulation->do_metropolis_steps(relaxation_steps, beta);

  std::vector<double> log_percentages;
  log_percentages.push_back(0.001);
  log_percentages.push_back(0.002);
  log_percentages.push_back(0.005);
  log_percentages.push_back(0.01);
  log_percentages.push_back(0.015);
  log_percentages.push_back(0.02);
  log_percentages.push_back(0.025);
  log_percentages.push_back(0.05);
  log_percentages.push_back(0.075);
  log_percentages.push_back(0.1);
  log_percentages.push_back(0.15);
  log_percentages.push_back(0.15);
  log_percentages.push_back(0.2);
  log_percentages.push_back(0.25);
  log_percentages.push_back(0.3);
  log_percentages.push_back(0.4);
  log_percentages.push_back(0.5);
  log_percentages.push_back(0.6);
  log_percentages.push_back(0.7);
  log_percentages.push_back(0.8);
  log_percentages.push_back(0.9);
  log_percentages.push_back(1.);

  std::vector<double>::const_iterator next_percentage = log_percentages.begin();

  for (uint32_t i = 0; i < num_measurements; i++)
    {
      const double percentage = (double)i / (double)num_measurements;
      if (percentage >= *next_percentage)
	{
	  BOOST_LOG_TRIVIAL(info) << "Simulation is  " << percentage << " finished.";
	  next_percentage++;
	}

      metropolis_simulation->do_metropolis_steps(steps_between_measurements, beta);
      measurement_handler(metropolis_simulation);
    }

  delete hard_sphere_configuration;
  delete metropolis_simulation;
}
