// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_CollisionFunctor_SimpleGeometries.hpp
 * \brief Simple Geometries CollisionFunctor test -- header
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_CF_SIMPLE_GEOMETRIES_HPP
#define TEST_CF_SIMPLE_GEOMETRIES_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <CollisionFunctor_SimpleGeometries.hpp>
#include <Disc.hpp>

class TestCFSimpleGeometries : CppUnit::TestFixture
{
private:
  mcchd::coordinate_type extents;

  mcchd::Disc collides_with_sphere_from_inside;
  mcchd::Disc collides_with_sphere_from_outside;
  mcchd::Disc inside_sphere;
  mcchd::Disc outside_sphere;
  mcchd::Disc collides_with_cylinder_from_inside;
  mcchd::Disc collides_with_cylinder_from_outside;
  mcchd::Disc inside_cylinder;
  mcchd::Disc outside_cylinder;
public:
  static CppUnit::Test* suite();

  void setUp();
  void tearDown();

  void test_collision_sphere();
  void test_collision_cylinder();
};


#endif
