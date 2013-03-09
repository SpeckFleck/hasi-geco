// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_HardDiscs.hpp
 * \brief Header for tests of the Hard Discs class
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_HARDDISCS_HPP
#define TEST_HARDDISCS_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <HardDiscs.hpp>
#include <random_boost_mt19937.hpp>
#include <CollisionFunctor_SingularDefects.hpp>

class TestHardDiscs : CppUnit::TestFixture
{
private:
  mcchd::HardDiscs<Boost_MT19937, mcchd::CF_PointDefect>* hard_disc_configuration;
public:
  static CppUnit::Test* suite();
  
  void setUp();
  void tearDown();

  void test_placement();
  void test_overlap();
};


#endif
