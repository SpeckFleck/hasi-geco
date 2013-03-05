// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_mcchd_Metropolis.hpp
 * \brief Metropolis simulation as a test case -- header
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_MCCHD_METROPOLIS_HPP
#define TEST_MCCHD_METROPOLIS_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <random_boost_mt19937.hpp>
#include <metropolis.hpp>
#include <HardDiscs.hpp>
#include <CollisionFunctor_SingularDefects.hpp>

class TestMCCHDMetropolis : CppUnit::TestFixture
{
  typedef mcchd::HardDiscs<Boost_MT19937, mcchd::CF_Bulk> ConfigurationType;
  typedef mcchd::Step<Boost_MT19937, mcchd::CF_Bulk> StepType;
  typedef Mocasinns::Metropolis<ConfigurationType, StepType, Boost_MT19937> SimulationType;
private:
  ConfigurationType* test_configuration;
  SimulationType* test_simulation;
public:
  static CppUnit::Test* suite();
  
  void setUp();
  void tearDown();

  void test_metropolis();
};

#endif
