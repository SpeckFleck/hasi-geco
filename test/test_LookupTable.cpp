// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_LookupTable.cpp
 * \brief test mcchd lookup table
 * 
 * Contains tests for
 *  - getting neighbour lists
 *  - removing and inserting discs
 * \author Johannes Knauf
 */

#include "test_LookupTable.hpp"

CppUnit::Test* TestLookupTable::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestLookupTable");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestLookupTable>("LookupTable: test get neighbours function", &TestLookupTable::test_get_neighbours) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestLookupTable>("LookupTable: test remove and insert function", &TestLookupTable::test_remove_insert) );
  
  return suite_of_tests;
}

void TestLookupTable::setUp()
{
  mcchd::coordinate_type extents = {{5., 5., 5.}};
  
  disc_table = new mcchd::LookupTable(extents);
  test_discs.push_back(new mcchd::Disc(mcchd::Point(1,1,1), 0));
  test_discs.push_back(new mcchd::Disc(mcchd::Point(3,2,1), 1));
  test_discs.push_back(new mcchd::Disc(mcchd::Point(1,2,4), 2));
  test_discs.push_back(new mcchd::Disc(mcchd::Point(1.8,1.4,4), 3));
  test_discs.push_back(new mcchd::Disc(mcchd::Point(0.8,1.4,4), 4));
  test_discs.push_back(new mcchd::Disc(mcchd::Point(3,3,3), 5));
  for (DiscPtrVec::iterator disc_it = test_discs.begin(); disc_it != test_discs.end(); disc_it++)
    disc_table->insert_disc(*disc_it);
}

void TestLookupTable::tearDown()
{
  while (test_discs.size() > 0)
    {
      delete test_discs.back();
      test_discs.pop_back();
    }
  delete disc_table;
}

void TestLookupTable::test_get_neighbours()
{
  mcchd::DiscVec neighbours = disc_table->get_neighbouring_discs(mcchd::Point(1,2,4));
  CPPUNIT_ASSERT(neighbours.size() == 3);
  mcchd::DiscVec::const_iterator neighbour_cit = neighbours.begin();

  CPPUNIT_ASSERT((*neighbour_cit)->get_center() == mcchd::Point(0.8,1.4,4) || (*neighbour_cit)->get_center() == mcchd::Point(1.8,1.4,4) || (*neighbour_cit)->get_center() == mcchd::Point(1,1,1) || (*neighbour_cit)->get_center() == mcchd::Point(1,2,4));
  neighbour_cit++;
  CPPUNIT_ASSERT((*neighbour_cit)->get_center() == mcchd::Point(0.8,1.4,4) || (*neighbour_cit)->get_center() == mcchd::Point(1.8,1.4,4) || (*neighbour_cit)->get_center() == mcchd::Point(1,1,1) || (*neighbour_cit)->get_center() == mcchd::Point(1,2,4));
  neighbour_cit++;
  CPPUNIT_ASSERT((*neighbour_cit)->get_center() == mcchd::Point(0.8,1.4,4) || (*neighbour_cit)->get_center() == mcchd::Point(1.8,1.4,4) || (*neighbour_cit)->get_center() == mcchd::Point(1,1,1) || (*neighbour_cit)->get_center() == mcchd::Point(1,2,4));
  neighbour_cit++;
  CPPUNIT_ASSERT(neighbour_cit == neighbours.end());
}

void TestLookupTable::test_remove_insert()
{
  for (DiscPtrVec::iterator disc_it = test_discs.begin(); disc_it != test_discs.end(); disc_it++)
    disc_table->remove_disc(*disc_it);

  CPPUNIT_ASSERT(disc_table->get_neighbouring_discs(mcchd::Point(1,2,4)).size() == 0);

  mcchd::Disc* new_test_disc = new mcchd::Disc(mcchd::Point(4.3, 2.1, 0.2), 6);
  disc_table->insert_disc(new_test_disc);
  CPPUNIT_ASSERT(disc_table->get_neighbouring_discs(mcchd::Point(4,2,1)).size() == 1);
  disc_table->remove_disc(new_test_disc);
  delete new_test_disc;

  for (DiscPtrVec::iterator disc_it = test_discs.begin(); disc_it != test_discs.end(); disc_it++)
    disc_table->insert_disc(*disc_it);

  
}
