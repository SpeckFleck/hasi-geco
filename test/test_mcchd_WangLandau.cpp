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

  result_comparison.push_back(0.);
  result_comparison.push_back(5.8161450778);
  result_comparison.push_back(10.9645807891);
  result_comparison.push_back(15.6774090969);
  result_comparison.push_back(20.0836287873);
  result_comparison.push_back(24.2419137538);
  result_comparison.push_back(28.2213670391);
  result_comparison.push_back(32.0682601872);
  result_comparison.push_back(35.7351328159);
  result_comparison.push_back(39.2550447199);
  result_comparison.push_back(42.6762485371);
  result_comparison.push_back(45.9880698046);
  result_comparison.push_back(49.1824641821);
  result_comparison.push_back(52.3407976914);
  result_comparison.push_back(55.3997966365);
  result_comparison.push_back(58.3750841805);
  result_comparison.push_back(61.3025355308);
  result_comparison.push_back(64.1229665466);
  result_comparison.push_back(66.9205122412);
  result_comparison.push_back(69.6239927783);
  result_comparison.push_back(72.2803025334);
  result_comparison.push_back(74.8819081520);
  result_comparison.push_back(77.4159496799);
  result_comparison.push_back(79.8961693695);
  result_comparison.push_back(82.2581928733);
  result_comparison.push_back(84.5878395027);
  result_comparison.push_back(86.8268693738);
  result_comparison.push_back(89.0133738344);
  result_comparison.push_back(91.2358822773);
  result_comparison.push_back(93.4233038661);
  result_comparison.push_back(95.4951959444);
  result_comparison.push_back(97.5395612873);
  result_comparison.push_back(99.5403010390);
  result_comparison.push_back(101.5314208484);
  result_comparison.push_back(103.4812032490);
  result_comparison.push_back(105.3645230600);
  result_comparison.push_back(107.2281394981);
  result_comparison.push_back(108.9713942638);
  result_comparison.push_back(110.7404431370);
  result_comparison.push_back(112.4409571830);
  result_comparison.push_back(114.1288963390);
  result_comparison.push_back(115.7544466482);
  result_comparison.push_back(117.3240312907);
  result_comparison.push_back(118.8680843827);
  result_comparison.push_back(120.4425030774);
  result_comparison.push_back(121.9558394229);
  result_comparison.push_back(123.4521269076);
  result_comparison.push_back(124.9035888135);
  result_comparison.push_back(126.3272075438);
  result_comparison.push_back(127.6865595775);
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
      //std::cout << std::setprecision(100) << entropy << std::endl;
      CPPUNIT_ASSERT((expected == 0. && entropy == 0.) || (abs(entropy - expected) < expected/1000.)); // test if precise to +- 0.1%
    }
}
