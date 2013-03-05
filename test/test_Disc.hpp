// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_Disc.hpp
 * \brief Header Unit Tests mcchd::Disc
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_DISC_HPP
#define TEST_DISC_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <Disc.hpp>

class TestDisc : CppUnit::TestFixture
{
private:
  mcchd::Disc origin;
  mcchd::Disc to_move;
  mcchd::Disc overlaps_origin;
  mcchd::Disc does_not_overlap_origin;
public:
  static CppUnit::Test* suite();
  
  void setUp();
  void tearDown();

  void test_distance();
  void test_overlap();
  void test_translate();
  void test_equality();
};


#endif

