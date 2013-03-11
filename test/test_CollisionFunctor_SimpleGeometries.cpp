// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_CollisionFunctor_NodalSurfaces.cpp
 * \brief Nodal surface CollisionFunctor test
 * 
 * Will contain tests for:
 *  - collision with sphere from inside and outside
 *  - collision with cylinder from inside and outside
 * 
 * \author Johannes Knauf
 */

#include "test_CollisionFunctor_SimpleGeometries.hpp"

CppUnit::Test* TestCFSimpleGeometries::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestCollisionFunctor_SimpleGeometries");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSimpleGeometries>("Collision Functor Simple Geometries: test sphere -- inside and outside", &TestCFSimpleGeometries::test_collision_sphere) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSimpleGeometries>("Collision Functor Simple Geometries: test cylinder -- inside and outside", &TestCFSimpleGeometries::test_collision_cylinder) );

  return suite_of_tests;
}

void TestCFSimpleGeometries::setUp()
{
  mcchd::coordinate_type new_extents = {{4., 6., 3.}};
  extents = new_extents;

  collides_with_sphere_from_inside = mcchd::Disc(mcchd::Point(), 0);
  collides_with_sphere_from_outside = mcchd::Disc(mcchd::Point(), 0);
  inside_sphere = mcchd::Disc(mcchd::Point(), 0);
  outside_sphere = mcchd::Disc(mcchd::Point(), 0);
  collides_with_cylinder_from_inside = mcchd::Disc(mcchd::Point(), 0);
  collides_with_cylinder_from_outside = mcchd::Disc(mcchd::Point(), 0);
  inside_cylinder = mcchd::Disc(mcchd::Point(), 0);
  outside_cylinder = mcchd::Disc(mcchd::Point(), 0);
}

void TestCFSimpleGeometries::tearDown()
{
}

void TestCFSimpleGeometries::test_collision_sphere()
{
  mcchd::CF_InnerSphere container_inner_sphere(extents);
  mcchd::CF_OuterSphere container_outer_sphere(extents);
}

void TestCFSimpleGeometries::test_collision_cylinder()
{
  mcchd::CF_InnerCylinder container_inner_cylinder(extents);
  mcchd::CF_OuterCylinder container_outer_cylinder(extents);
}
