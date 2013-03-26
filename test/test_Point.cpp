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

#include <boost/array.hpp>
#include <vector>
#include <numeric>

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
  const mcchd::coordinate_type new_extents = {{4., 6., 3.}};
  extents = new_extents;
  test_point = new mcchd::Point();
}

void TestPoint::tearDown()
{
  delete test_point;
}

void TestPoint::test_distance()
{
  mcchd::Point origin = mcchd::Point(0, 0, 0);
  CPPUNIT_ASSERT(test_point->distance(origin) == 0);

  mcchd::Point new_point = mcchd::Point(3, 2, 1);
  CPPUNIT_ASSERT(new_point != origin);
  CPPUNIT_ASSERT(new_point-new_point == origin);
  CPPUNIT_ASSERT(new_point.absolute() == sqrt(pow(3.0, 2) + pow(2.0, 2) + pow(1.0, 2)));

  // PBC
  CPPUNIT_ASSERT(origin.distance(new_point, extents) == sqrt(pow(1.0, 2) + pow(2.0, 2) + pow(1.0, 2)));
  mcchd::Point shifted_origin = mcchd::Point(extents);
  CPPUNIT_ASSERT(origin.distance(shifted_origin, extents) == 0.);
}

void TestPoint::test_random()
{
  Boost_MT19937 rng;
  
  boost::array<std::vector<double>, 3> mean_coor;

  for (uint32_t i = 0; i < 10000; i++)
    {
      mcchd::Point random_point(&rng, extents);
      CPPUNIT_ASSERT((0 <= random_point.get_coor(0)) && (random_point.get_coor(0) <= 4.));
      CPPUNIT_ASSERT((0 <= random_point.get_coor(1)) && (random_point.get_coor(1) <= 6.));
      CPPUNIT_ASSERT((0 <= random_point.get_coor(2)) && (random_point.get_coor(2) <= 3.));
      for(uint8_t j = 0; j < 3; j++)
	{
	  mean_coor[j].push_back(random_point.get_coor(j));
	}
    }
  
  CPPUNIT_ASSERT(((std::accumulate(mean_coor[0].begin(), mean_coor[0].end(), 0) / (double)mean_coor[0].size()) - 4./2.) < 0.1);
  CPPUNIT_ASSERT(((std::accumulate(mean_coor[1].begin(), mean_coor[1].end(), 0) / (double)mean_coor[1].size()) - 6./2.) < 0.1);
  CPPUNIT_ASSERT(((std::accumulate(mean_coor[2].begin(), mean_coor[2].end(), 0) / (double)mean_coor[2].size()) - 3./2.) < 0.1);
 
}
