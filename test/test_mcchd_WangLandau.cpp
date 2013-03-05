// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_mcchd_WangLandau.cpp
 * \brief Wang Landau simulation implementation as a test case
 * 
 * The following tests are performed:
 *  - run a simple Wang Landau simulation; compare resulting density of states with presampled version
 * 
 * \author Johannes Knauf
 */

#include "test_mcchd_WangLandau.hpp"
#include <metropolis.hpp>

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

CppUnit::Test* TestMCCHDWangLandau::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestMCCHDWangLandau");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestMCCHDWangLandau>("Mocasinns Wang Landau: interface compatibility and integration", &TestMCCHDWangLandau::test_wanglandau) );
  
  return suite_of_tests;
}

void TestMCCHDWangLandau::setUp()
{
  mcchd::coordinate_type extents = {{7.,7.,7.}};
  test_configuration = new ConfigurationType(extents);

  parameters.modification_factor_initial = 1.0;
  parameters.modification_factor_final = 1e-15;
  parameters.modification_factor_multiplier = 0.5;
  parameters.flatness = 0.6;
  parameters.sweep_steps = 10000;
  parameters.energy_cutoff_use = true;
  parameters.energy_cutoff = 50;

  test_simulation = new SimulationType(parameters, test_configuration);

  // result_comparison was generated with seed 3, 1e-1 -- 1e-15, *0.5, =0.6, #10000, Emax 50
  result_comparison.push_back(0.0000000000000000e+00);
  result_comparison.push_back(4.6152914520008856e+00);
  result_comparison.push_back(8.8239636740803480e+00);
  result_comparison.push_back(1.2735492260557022e+01);
  result_comparison.push_back(1.6423658619065890e+01);
  result_comparison.push_back(1.9912805404148749e+01);
  result_comparison.push_back(2.3260657602133968e+01);
  result_comparison.push_back(2.6458534091402676e+01);
  result_comparison.push_back(2.9560732222938508e+01);
  result_comparison.push_back(3.2546972892416584e+01);
  result_comparison.push_back(3.5431779471969080e+01);
  result_comparison.push_back(3.8227801695839744e+01);
  result_comparison.push_back(4.0935835561060287e+01);
  result_comparison.push_back(4.3575382815551976e+01);
  result_comparison.push_back(4.6135974744085026e+01);
  result_comparison.push_back(4.8655317141349563e+01);
  result_comparison.push_back(5.1129437095592138e+01);
  result_comparison.push_back(5.3528513350136386e+01);
  result_comparison.push_back(5.5899008651299262e+01);
  result_comparison.push_back(5.8203911795067064e+01);
  result_comparison.push_back(6.0469779127105312e+01);
  result_comparison.push_back(6.2679587310819642e+01);
  result_comparison.push_back(6.4866416406440365e+01);
  result_comparison.push_back(6.6961457398759450e+01);
  result_comparison.push_back(6.9034284954445368e+01);
  result_comparison.push_back(7.1073443543054751e+01);
  result_comparison.push_back(7.3054959006508028e+01);
  result_comparison.push_back(7.5007953910187865e+01);
  result_comparison.push_back(7.6937998218692499e+01);
  result_comparison.push_back(7.8856180284710106e+01);
  result_comparison.push_back(8.0720388074807587e+01);
  result_comparison.push_back(8.2523713925569538e+01);
  result_comparison.push_back(8.4295716401082615e+01);
  result_comparison.push_back(8.6031212926867084e+01);
  result_comparison.push_back(8.7719895211324669e+01);
  result_comparison.push_back(8.9415482249580108e+01);
  result_comparison.push_back(9.1080095274136823e+01);
  result_comparison.push_back(9.2706593796027164e+01);
  result_comparison.push_back(9.4316606492931840e+01);
  result_comparison.push_back(9.5923420019937225e+01);
  result_comparison.push_back(9.7503896903153304e+01);
  result_comparison.push_back(9.9046288477726051e+01);
  result_comparison.push_back(1.0056083315351182e+02);
  result_comparison.push_back(1.0207284812213612e+02);
  result_comparison.push_back(1.0354830096562603e+02);
  result_comparison.push_back(1.0503056706067954e+02);
  result_comparison.push_back(1.0645645234099898e+02);
  result_comparison.push_back(1.0786378619241178e+02);
  result_comparison.push_back(1.0925493457717842e+02);
  result_comparison.push_back(1.1063152798144056e+02);
}

void TestMCCHDWangLandau::tearDown()
{
  delete test_configuration;
  delete test_simulation;
}

void TestMCCHDWangLandau::test_wanglandau()
{
  test_simulation->set_random_seed(1);

  test_simulation->do_wang_landau_simulation();

  Mocasinns::Histograms::Histocrete<energy_type, double> entropy_estimation = test_simulation->get_density_of_states();
  for (Mocasinns::Histograms::Histocrete<energy_type, double>::iterator ent_it = entropy_estimation.begin(); ent_it != entropy_estimation.end(); ent_it++)
    {
      const energy_type energy = (*ent_it).first;
      const double entropy = (*ent_it).second;
      const double expected = result_comparison[energy];
      CPPUNIT_ASSERT((expected == 0. && entropy == 0.) || (abs(entropy - expected) < expected/1000.)); // test if precise to +- 0.1%
    }
}
