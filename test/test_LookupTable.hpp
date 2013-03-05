// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_LookupTable.hpp
 * \brief Header mcchd lookup table test
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_LOOKUPTABLE_HPP
#define TEST_LOOKUPTABLE_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <LookupTable.hpp>

class TestLookupTable : CppUnit::TestFixture
{
private:
  mcchd::LookupTable *disc_table;
public:
  static CppUnit::Test* suite();

  void setUp();
  void tearDown();

  void test_get_neighbours();
  void test_remove_insert();
};

#endif
