// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_CollisionFunctor_SingularDefects.cpp
 * \brief Singular Defects CollisionFunctor test
 * 
 * Will contain tests for:
 *  - Point Defect
 *  - Line Defect
 *  - Plane Defect
 * 
 * \author Johannes Knauf
 */

#include "test_CollisionFunctor_SingularDefects.hpp"

CppUnit::Test* TestCFSingularDefects::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestCollisionFunctor_SingularDefects");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSingularDefects>("Collision Functor Singular Defects: test bulk -- no defects", &TestCFSingularDefects::test_collision_bulk) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSingularDefects>("Collision Functor Singular Defects: test point defect", &TestCFSingularDefects::test_collision_point) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSingularDefects>("Collision Functor Singular Defects: test line defect", &TestCFSingularDefects::test_collision_line) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSingularDefects>("Collision Functor Singular Defects: test plane defect", &TestCFSingularDefects::test_collision_plane) );


  return suite_of_tests;
}

void TestCFSingularDefects::setUp()
{
  mcchd::coordinate_type new_extents = {{4., 6., 3.}};
  extents = new_extents;

  collides_with_point_line_plane = mcchd::Disc(mcchd::Point(2.2, 2.8, 1.6), 0);
  collides_with_line_plane = mcchd::Disc(mcchd::Point(1.9, 3.1, 2.5), 0);
  collides_with_plane = mcchd::Disc(mcchd::Point(1.7, 1.0, 1.4), 0);
  collides_with_nothing = mcchd::Disc(mcchd::Point(0.3, 0.3, 0.3), 0);
}

void TestCFSingularDefects::tearDown()
{
}

/// generate random points -- they should never collide
void TestCFSingularDefects::test_collision_bulk()
{
  mcchd::CF_Bulk container_bulk(extents);
  Boost_MT19937 rng;
  
  for (uint32_t i = 0; i < 10000; i++)
    {
      mcchd::Point random_point(&rng, extents);
      mcchd::Disc random_disc(random_point, 0);
      CPPUNIT_ASSERT(! container_bulk.collides_with(random_disc));
    }
}

void TestCFSingularDefects::test_collision_point()
{
  mcchd::CF_PointDefect container_point(extents);
  
  CPPUNIT_ASSERT(container_point.collides_with(collides_with_point_line_plane));
  CPPUNIT_ASSERT(! container_point.collides_with(collides_with_line_plane));
  CPPUNIT_ASSERT(! container_point.collides_with(collides_with_plane));
  CPPUNIT_ASSERT(! container_point.collides_with(collides_with_nothing));
}

void TestCFSingularDefects::test_collision_line()
{
  mcchd::CF_LineDefect container_line(extents);

  CPPUNIT_ASSERT(container_line.collides_with(collides_with_point_line_plane));
  CPPUNIT_ASSERT(container_line.collides_with(collides_with_line_plane));
  CPPUNIT_ASSERT(! container_line.collides_with(collides_with_plane));
  CPPUNIT_ASSERT(! container_line.collides_with(collides_with_nothing));
}

void TestCFSingularDefects::test_collision_plane()
{
  mcchd::CF_PlaneDefect container_plane(extents);

  CPPUNIT_ASSERT(container_plane.collides_with(collides_with_point_line_plane));
  CPPUNIT_ASSERT(container_plane.collides_with(collides_with_line_plane));
  CPPUNIT_ASSERT(container_plane.collides_with(collides_with_plane));
  CPPUNIT_ASSERT(! container_plane.collides_with(collides_with_nothing));
}
