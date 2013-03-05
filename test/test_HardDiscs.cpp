// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_HardDiscs.cpp
 * \brief tests for the hard discs class
 * 
 * The following tests are performed:
 *  - placement of discs
 *  - removal of discs
 *  - check overlap with existing discs
 * 
 * \author Johannes Knauf
 */

#include "test_HardDiscs.hpp"

CppUnit::Test* TestHardDiscs::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestHardDiscs");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestHardDiscs>("Hard Discs: test insert/remove disc functions", &TestHardDiscs::test_placement) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestHardDiscs>("Hard Discs: test overlap test", &TestHardDiscs::test_overlap) );
  
  return suite_of_tests;
}

void TestHardDiscs::setUp()
{
  mcchd::coordinate_type extents = {{5., 5., 5.}};

  hard_disc_configuration = new mcchd::HardDiscs<Boost_MT19937, mcchd::CF_PointDefect>(extents);
  hard_disc_configuration->insert_disc(mcchd::Point(3,4,1));
  hard_disc_configuration->insert_disc(mcchd::Point(3,4,4));
}

void TestHardDiscs::tearDown()
{
  delete hard_disc_configuration;
}

void TestHardDiscs::test_placement()
{
  CPPUNIT_ASSERT(hard_disc_configuration->get_number_of_discs() == 2);
  hard_disc_configuration->insert_disc(mcchd::Point(1,1,1));
  CPPUNIT_ASSERT(hard_disc_configuration->get_number_of_discs() == 3);
  hard_disc_configuration->insert_disc(mcchd::Point(3,1,1));
  CPPUNIT_ASSERT(hard_disc_configuration->get_number_of_discs() == 4);
  hard_disc_configuration->remove_disc(2);
  CPPUNIT_ASSERT(hard_disc_configuration->get_number_of_discs() == 3);
  hard_disc_configuration->remove_disc(2);
  CPPUNIT_ASSERT(hard_disc_configuration->get_number_of_discs() == 2);
}

void TestHardDiscs::test_overlap()
{
  CPPUNIT_ASSERT(! hard_disc_configuration->is_overlapping(mcchd::Disc(mcchd::Point(1,1,1), 1)));
  CPPUNIT_ASSERT(! hard_disc_configuration->is_overlapping(mcchd::Disc(mcchd::Point(3.8,4.8,1.8), 1)));
  CPPUNIT_ASSERT(hard_disc_configuration->is_overlapping(mcchd::Disc(mcchd::Point(3,4,1), 1)));
  CPPUNIT_ASSERT(hard_disc_configuration->is_overlapping(mcchd::Disc(mcchd::Point(2.9,4.1,1.2), 1)));
  CPPUNIT_ASSERT(hard_disc_configuration->is_overlapping(mcchd::Disc(mcchd::Point(2.4,2.4,2.6), 1))); // overlapping with container, i.e. point defect in center
}

