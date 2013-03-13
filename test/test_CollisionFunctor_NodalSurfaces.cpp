// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_CollisionFunctor_NodalSurfaces.cpp
 * \brief Nodal surface CollisionFunctor test
 * 
 * Will contain tests for:
 *  - P surface
 *  - D surface
 *  - G surface
 *  - IWP surface
 *
 * tests should be automized and just test symmetries and so on for random points in a unique way.
 * 
 * \author Johannes Knauf
 */

#include "test_CollisionFunctor_NodalSurfaces.hpp"

CppUnit::Test* TestCFNodalSurfaces::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestCollisionFunctor_NodalSurfaces");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFNodalSurfaces>("Collision Functor Nodal Surfaces: test P surface", &TestCFNodalSurfaces::test_collision_p) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFNodalSurfaces>("Collision Functor Nodal Surfaces: test point defect", &TestCFNodalSurfaces::test_collision_d) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFNodalSurfaces>("Collision Functor Nodal Surfaces: test line defect", &TestCFNodalSurfaces::test_collision_g) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFNodalSurfaces>("Collision Functor Nodal Surfaces: test plane defect", &TestCFNodalSurfaces::test_collision_iwp) );

  return suite_of_tests;
}

void TestCFNodalSurfaces::setUp()
{
  mcchd::coordinate_type new_extents = {{4., 6., 3.}};
  extents = new_extents;
}

void TestCFNodalSurfaces::tearDown()
{
}

void TestCFNodalSurfaces::test_collision_p()
{
  mcchd::CF_PSurface container_p(extents);
}

void TestCFNodalSurfaces::test_collision_d()
{
  mcchd::CF_DSurface container_d(extents);
}

void TestCFNodalSurfaces::test_collision_g()
{
  mcchd::CF_GSurface container_g(extents);
}

void TestCFNodalSurfaces::test_collision_iwp()
{
  mcchd::CF_InnerIWPSurface container_inner_iwp(extents);
  mcchd::CF_OuterIWPSurface container_outer_iwp(extents);
}
