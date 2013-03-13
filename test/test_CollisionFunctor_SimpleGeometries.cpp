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
  mcchd::coordinate_type new_extents = {{10., 10., 10.}}; // non-cubic extents throw error -- should be tested as well
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
  const mcchd::coordinate_type bad_extents_1 = {{4., 5., 5.}};
  const mcchd::coordinate_type bad_extents_2 = {{5., 3., 5.}};
  const mcchd::coordinate_type bad_extents_3 = {{5., 5., 1.}};
  const mcchd::coordinate_type good_extents_inner = {{5., 5., 5.}};
  const mcchd::coordinate_type good_extents = {{8., 8., 8.}};

  CPPUNIT_ASSERT_THROW(mcchd::CF_InnerSphere x(bad_extents_1), mcchd::bad_extents_exception_sphere); 
  CPPUNIT_ASSERT_THROW(mcchd::CF_InnerSphere x(bad_extents_2), mcchd::bad_extents_exception_sphere);
  CPPUNIT_ASSERT_THROW(mcchd::CF_InnerSphere x(bad_extents_3), mcchd::bad_extents_exception_sphere);
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_InnerSphere x(good_extents_inner));
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_InnerSphere x(good_extents));

  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterSphere x(bad_extents_1), mcchd::bad_extents_exception_sphere);
  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterSphere x(bad_extents_2), mcchd::bad_extents_exception_sphere);
  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterSphere x(bad_extents_3), mcchd::bad_extents_exception_sphere);
  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterSphere x(good_extents_inner), mcchd::bad_extents_exception_sphere);
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_OuterSphere x(good_extents));

  mcchd::CF_InnerSphere container_inner_sphere(extents);
  mcchd::CF_OuterSphere container_outer_sphere(extents);
}

void TestCFSimpleGeometries::test_collision_cylinder()
{
  const mcchd::coordinate_type bad_extents_1 = {{4., 5., 5.}};
  const mcchd::coordinate_type bad_extents_2 = {{5., 3., 5.}};
  const mcchd::coordinate_type good_extents_inner_1 = {{5., 5., 1.}};
  const mcchd::coordinate_type good_extents_inner_2 = {{5., 5., 5.}};
  const mcchd::coordinate_type good_extents_1 = {{8., 8., 1.}};
  const mcchd::coordinate_type good_extents_2 = {{8., 8., 8.}};

  CPPUNIT_ASSERT_THROW(mcchd::CF_InnerCylinder x(bad_extents_1), mcchd::bad_extents_exception_cylinder);
  CPPUNIT_ASSERT_THROW(mcchd::CF_InnerCylinder x(bad_extents_2), mcchd::bad_extents_exception_cylinder);
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_InnerCylinder x(good_extents_inner_1));
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_InnerCylinder x(good_extents_inner_2));
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_InnerCylinder x(good_extents_1));
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_InnerCylinder x(good_extents_2));

  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterCylinder x(bad_extents_1), mcchd::bad_extents_exception_cylinder);
  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterCylinder x(bad_extents_2), mcchd::bad_extents_exception_cylinder);
  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterCylinder x(good_extents_inner_1), mcchd::bad_extents_exception_cylinder);
  CPPUNIT_ASSERT_THROW(mcchd::CF_OuterCylinder x(good_extents_inner_2), mcchd::bad_extents_exception_cylinder);
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_OuterCylinder x(good_extents_1));
  CPPUNIT_ASSERT_NO_THROW(mcchd::CF_OuterCylinder x(good_extents_2));

  mcchd::CF_InnerCylinder container_inner_cylinder(extents);
  mcchd::CF_OuterCylinder container_outer_cylinder(extents);
}
