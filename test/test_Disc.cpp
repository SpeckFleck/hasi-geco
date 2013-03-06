// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_Disc.cpp
 * \brief Unit Tests for mcchd::Disc
 * 
 * Contains the tests for
 *  - distance
 *  - overlap
 *  - translation -- tests get_center as well
 *  - equality
 * 
 * \author Johannes Knauf
 */

#include <cmath>
#include "test_Disc.hpp"

CppUnit::Test* TestDisc::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestDisc");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestDisc>("Disc: test distance function", &TestDisc::test_distance) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestDisc>("Disc: test overlap test", &TestDisc::test_overlap) );  
  suite_of_tests->addTest( new CppUnit::TestCaller<TestDisc>("Disc: test translation method", &TestDisc::test_translate) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestDisc>("Disc: test equality operator", &TestDisc::test_equality) );
  
  return suite_of_tests;
}

void TestDisc::setUp()
{
  origin = mcchd::Disc(0);
  to_move = mcchd::Disc(1);
  overlaps_origin = mcchd::Disc(mcchd::Point(0.5, 0.5, 0.5), 2);
  does_not_overlap_origin = mcchd::Disc(mcchd::Point(2, 5, 0), 3);
}

void TestDisc::tearDown()
{
}

void TestDisc::test_distance()
{
  CPPUNIT_ASSERT(origin.distance(to_move) == 0.); // function itself
  CPPUNIT_ASSERT(origin.distance(to_move) == to_move.distance(origin)); // symmetry
  CPPUNIT_ASSERT(origin.distance(overlaps_origin) == sqrt(3* 0.5*0.5)); // function itself
  CPPUNIT_ASSERT(origin.distance(overlaps_origin) == overlaps_origin.distance(origin)); // symmetry
  CPPUNIT_ASSERT(origin.distance(does_not_overlap_origin) == sqrt(2.*2. + 5.*5. + 0.)); // function itself
  CPPUNIT_ASSERT(origin.distance(does_not_overlap_origin) == does_not_overlap_origin.distance(origin)); // symmetry
}

void TestDisc::test_overlap()
{
  CPPUNIT_ASSERT(origin.is_overlapping(overlaps_origin)); // function itself
  CPPUNIT_ASSERT(origin.is_overlapping(overlaps_origin) == overlaps_origin.is_overlapping(origin)); // symmetry
  CPPUNIT_ASSERT(! (origin.is_overlapping(does_not_overlap_origin))); // function itself
  CPPUNIT_ASSERT(origin.is_overlapping(does_not_overlap_origin) == does_not_overlap_origin.is_overlapping(origin)); // symmetry
}

void TestDisc::test_translate()
{
  to_move.translate_to(mcchd::Point(0.5, 0.5, 0.5));
  CPPUNIT_ASSERT((to_move == to_move));
  CPPUNIT_ASSERT(!(to_move == overlaps_origin) && (to_move.get_center() == overlaps_origin.get_center()));
  CPPUNIT_ASSERT(to_move.distance(overlaps_origin) == 0.);
  to_move = mcchd::Disc(1);
}

void TestDisc::test_equality()
{
  CPPUNIT_ASSERT(origin == origin);
  CPPUNIT_ASSERT(origin != to_move);
}
