// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_Step.cpp
 * \brief test for Step class implementation
 * 
 * As the Step class is deeply integrated with the HardDiscs class, it needs an instance of the latter.
 *
 * The following tests are performed:
 *  - none yet
 * 
 * \author Johannes Knauf
 */

#include "test_Step.hpp"

CppUnit::Test* TestStep::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestStep");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestStep>("Step: test execute method", &TestStep::test_execute) );
  
  return suite_of_tests;
}

void TestStep::setUp()
{
  mcchd::coordinate_type extents;
  extents[0] = 5.;
  extents[1] = 5.;
  extents[2] = 5.;

  hard_disc_configuration = new mcchd::HardDiscs<Boost_MT19937, mcchd::CF_PointDefect>(extents);
}

void TestStep::tearDown()
{
  delete hard_disc_configuration;
}

void TestStep::test_execute()
{
  mcchd::Step<Boost_MT19937, mcchd::CF_PointDefect> test_step();
}
