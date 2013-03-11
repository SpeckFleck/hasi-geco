// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_Step.hpp
 * \brief test for Step class -- header
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_STEP_HPP
#define TEST_STEP_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <Step.hpp>
#include <HardDiscs.hpp>
#include <CollisionFunctor_SingularDefects.hpp>

class TestStep : CppUnit::TestFixture
{
private:
  mcchd::HardDiscs<Boost_MT19937, mcchd::CF_Bulk>* hard_disc_configuration;
  Boost_MT19937 rng;
public:
  static CppUnit::Test* suite();
  
  void setUp();
  void tearDown();

  void test_execute();
};



#endif
