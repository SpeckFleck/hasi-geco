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

  hard_disc_configuration = new TestStep::HardDiscSpace(extents);
}

void TestStep::tearDown()
{
  delete hard_disc_configuration;
}

void TestStep::test_execute()
{
  Boost_MT19937 rng;

  bool tested_failing_insert_at_least_once = false;
  bool tested_successful_insert_at_least_once = false;
  bool tested_failing_remove_at_least_once = false;
  bool tested_successful_remove_at_least_once = false;

  for (uint32_t i = 0; i < 10000; i++)
    {
      mcchd::Step<HardDiscSpace> random_step = hard_disc_configuration->propose_step(&rng);

      const mcchd::energy_type energy_before = hard_disc_configuration->energy();
      const mcchd::energy_type energy_change = random_step.delta_E();
      CPPUNIT_ASSERT(energy_change == 1 || energy_change == -1);

      if (random_step.is_executable())
	{
	  if (random_step.is_remove_step())
	    {
	      tested_successful_remove_at_least_once = true;
	    }
	  else
	    {
	      tested_successful_insert_at_least_once = true;
	    }

	  random_step.execute();
	  const mcchd::energy_type energy_after = hard_disc_configuration->energy();
	  CPPUNIT_ASSERT(energy_before + energy_change == energy_after);
	}
      else
	{
	  if (random_step.is_remove_step())
	    {
	      CPPUNIT_ASSERT(hard_disc_configuration->get_number_of_discs() == 0);
	      tested_failing_remove_at_least_once = true;
	    }
	  else
	    {
	      CPPUNIT_ASSERT(hard_disc_configuration->get_number_of_discs() > 0);
	      tested_failing_insert_at_least_once = true;
	    }
	}

    }

  CPPUNIT_ASSERT(tested_failing_insert_at_least_once && 
		 tested_successful_insert_at_least_once && 
		 tested_failing_remove_at_least_once && 
		 tested_successful_remove_at_least_once);
}
