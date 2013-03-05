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
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSingularDefects>("Collision Functor Singular Defects: test point defect", &TestCFSingularDefects::test_collision_point) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSingularDefects>("Collision Functor Singular Defects: test line defect", &TestCFSingularDefects::test_collision_line) );
  suite_of_tests->addTest( new CppUnit::TestCaller<TestCFSingularDefects>("Collision Functor Singular Defects: test plane defect", &TestCFSingularDefects::test_collision_plane) );


  return suite_of_tests;
}

void TestCFSingularDefects::setUp()
{
}

void TestCFSingularDefects::tearDown()
{
}

void TestCFSingularDefects::test_collision_point()
{
}

void TestCFSingularDefects::test_collision_line()
{
}

void TestCFSingularDefects::test_collision_plane()
{
}
