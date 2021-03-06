// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_Point.hpp
 * \brief Header Unit Tests mcchd::Point
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_POINT_HPP
#define TEST_POINT_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <Point.hpp>
#include <mocasinns/random/boost_random.hpp>
typedef Mocasinns::Random::Boost_MT19937 Boost_MT19937;

class TestPoint : CppUnit::TestFixture
{
private:
  mcchd::Point* test_point;
  mcchd::coordinate_type extents;
public:
  static CppUnit::Test* suite();
  
  void setUp();
  void tearDown();

  void test_distance();
  void test_random();
};

#endif
