// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_mcchd_WangLandau.hpp
 * \brief WangLandau simulation as a test case -- header
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_MCCHD_WANGLANDAU_HPP
#define TEST_MCCHD_WANGLANDAU_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <mocasinns/random/boost_random.hpp>
#include <mocasinns/histograms/histocrete.hpp>
#include <mocasinns/wang_landau.hpp>
#include <HardDiscs.hpp>
#include <CollisionFunctor_SingularDefects.hpp>

typedef Mocasinns::Random::Boost_MT19937 Boost_MT19937;

class TestMCCHDWangLandau : CppUnit::TestFixture
{
  typedef mcchd::disc_id_type energy_type;
  typedef mcchd::HardDiscs<mcchd::CF_Bulk> ConfigurationType;
  typedef mcchd::Step<mcchd::CF_Bulk> StepType;
  typedef Mocasinns::WangLandau<ConfigurationType, StepType, energy_type, Mocasinns::Histograms::Histocrete, Boost_MT19937> SimulationType;
private:
  ConfigurationType* test_configuration;
  SimulationType* test_simulation;
  SimulationType::Parameters<energy_type> parameters;
  std::vector<double> result_comparison;
public:
  static CppUnit::Test* suite();
  
  void setUp();
  void tearDown();

  void test_wanglandau();
};

#endif
