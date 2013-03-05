// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_CollisionFunctor_SingularDefects.hpp
 * \brief Singular Defects CollisionFunctor test -- header
 * 
 * Contains the base structure of the CppUnit test.
 * 
 * \author Johannes Knauf
 */

#ifndef TEST_CF_SINGULAR_DEFECTS_HPP
#define TEST_CF_SINGULAR_DEFECTS_HPP

#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/Test.h>

#include <CollisionFunctor_SingularDefects.hpp>

class TestCFSingularDefects : CppUnit::TestFixture
{
private:
public:
  static CppUnit::Test* suite();

  void setUp();
  void tearDown();

  void test_collision_point();
  void test_collision_line();
  void test_collision_plane();
};


#endif
