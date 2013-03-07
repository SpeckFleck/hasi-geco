// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_Point.cpp
 * \brief Unit Tests for mcchd::Point
 * 
 * contains tests for:
 *  - distance
 *  - generation of random points
 * 
 * \author Johannes Knauf
 */

#include "test_Point.hpp"
#include <random_boost_mt19937.hpp>
#include <stdint.h>
#include <cmath>


CppUnit::Test* TestPoint::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestPoint");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestPoint>("Point: test distance function", &TestPoint::test_distance) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestPoint>("Point: test random point generator", &TestPoint::test_random) );
  
  return suite_of_tests;
}

void TestPoint::setUp()
{
  test_point = new mcchd::Point();
}

void TestPoint::tearDown()
{
  delete test_point;
}

void TestPoint::test_distance()
{
  mcchd::Point origin = mcchd::Point();
  CPPUNIT_ASSERT(test_point->distance(origin) == 0);

  mcchd::Point new_point = mcchd::Point(3, 2, 1);
  CPPUNIT_ASSERT(new_point != origin);
  CPPUNIT_ASSERT(new_point-new_point == origin);
  CPPUNIT_ASSERT(new_point.absolute() == sqrt(pow(3.0, 2) + pow(2.0, 2) + pow(1.0, 2)));
}

void TestPoint::test_random()
{
  mcchd::coordinate_type extents = {{4., 6., 3.}};

  Boost_MT19937 rng;

  for (uint32_t i = 0; i < 10000; i++)
    {
      mcchd::Point random_point(&rng, extents);
      CPPUNIT_ASSERT((0 <= random_point.get_coor(0)) && (random_point.get_coor(0) <= 4.));
      CPPUNIT_ASSERT((0 <= random_point.get_coor(1)) && (random_point.get_coor(1) <= 6.));
      CPPUNIT_ASSERT((0 <= random_point.get_coor(2)) && (random_point.get_coor(2) <= 3.));
    }
}
