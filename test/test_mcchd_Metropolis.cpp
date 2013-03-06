// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_mcchd_Metropolis.cpp
 * \brief Metropolis simulation implementation as a test case
 * 
 * The following tests are performed:
 *  - simulate 100*100 steps with beta (= - mu * beta in the grandcanonical case here) = 4; compare against values
 *  - simulate 100*100 steps with beta (= - mu * beta in the grandcanonical case here) = -4; compare against values
 *  - simulate 100*100 steps with beta (= - mu * beta in the grandcanonical case here) = 0; compare against values
 * 
 * \author Johannes Knauf
 */

#include "test_mcchd_Metropolis.hpp"
#include <metropolis.hpp>

CppUnit::Test* TestMCCHDMetropolis::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestMCCHDMetropolis");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestMCCHDMetropolis>("Mocasinns Metropolis: interface compatibility and integration", &TestMCCHDMetropolis::test_metropolis) );
  
  return suite_of_tests;
}

void TestMCCHDMetropolis::setUp()
{
  mcchd::coordinate_type extents = {{5., 5., 5.}};
  SimulationType::Parameters parameters;
  test_configuration = new ConfigurationType(extents);
  test_simulation = new SimulationType(parameters, test_configuration);
}

void TestMCCHDMetropolis::tearDown()
{
  delete test_configuration;
  delete test_simulation;
}

void TestMCCHDMetropolis::test_metropolis()
{
  double sum, peak;
  int n;

  // part 1: beta = 4
  sum = 0;
  n = 0;
  for (uint32_t i = 0; i < 100; i++)
  {
    n++;
    test_simulation->do_metropolis_steps(100, 4.);
    sum += test_simulation->get_config_space()->energy();
  }
  peak = sum / static_cast<double> (n);
  CPPUNIT_ASSERT(1. < peak && peak < 2.); 

  // part 2: beta = -4
  sum = 0;
  n = 0;
  for (uint32_t i = 0; i < 100; i++)
  {
    n++;
    test_simulation->do_metropolis_steps(1000, -4.);
    sum += test_simulation->get_config_space()->energy();
  }
  peak = sum / static_cast<double> (n);
  CPPUNIT_ASSERT(90. < peak); 

  // part 3: beta = 0
  sum = 0;
  n = 0;
  for (uint32_t i = 0; i < 100; i++)
  {
    n++;
    test_simulation->do_metropolis_steps(100, 0.);
    sum += test_simulation->get_config_space()->energy();
  }
  peak = sum / static_cast<double> (n);
  CPPUNIT_ASSERT(30. < peak && peak < 35.);


}
