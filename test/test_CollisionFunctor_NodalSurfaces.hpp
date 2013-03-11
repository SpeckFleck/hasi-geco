// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_CollisionFunctor_NodalSurfaces.hpp
 * \brief Nodal surface CollisionFunctor test -- header
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_CF_NODAL_SURFACES_HPP
#define TEST_CF_NODAL_SURFACES_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <CollisionFunctor_NodalSurfaces.hpp>
#include <Disc.hpp>

class TestCFNodalSurfaces : CppUnit::TestFixture
{
private:
  mcchd::coordinate_type extents;
public:
  static CppUnit::Test* suite();

  void setUp();
  void tearDown();

  void test_collision_p();
  void test_collision_d();
  void test_collision_g();
  void test_collision_iwp();
};


#endif
