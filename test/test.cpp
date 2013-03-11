// -*- coding: utf-8; -*-
/*!
 * 
 * \file test.cpp
 * \brief test program mocacohadi
 * 
 * Executes the tests
 *  - point
 *  - disc
 *  - collision functor singular defects
 *  - lookup table
 *  - step
 *  - hard dics
 *  - mocacohadi + mocasinns Metropolis
 *  - mocacohadi + mocasinns Wang Landau
 * 
 * \author Johannes Knauf
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>

#include "test_Point.hpp"
#include "test_Disc.hpp"
#include "test_CollisionFunctor_SingularDefects.hpp"
#include "test_CollisionFunctor_NodalSurfaces.hpp"
#include "test_CollisionFunctor_SimpleGeometries.hpp"
#include "test_LookupTable.hpp"
#include "test_Step.hpp"
#include "test_HardDiscs.hpp"
#include "test_mcchd_Metropolis.hpp"
#include "test_mcchd_WangLandau.hpp"

int main()
{

  CppUnit::TextUi::TestRunner runner;
  runner.addTest(TestPoint::suite());
  runner.addTest(TestDisc::suite());
  runner.addTest(TestCFSingularDefects::suite());
  runner.addTest(TestCFNodalSurfaces::suite());
  runner.addTest(TestCFSimpleGeometries::suite());
  runner.addTest(TestLookupTable::suite());
  runner.addTest(TestStep::suite());
  runner.addTest(TestHardDiscs::suite());
  runner.addTest(TestMCCHDMetropolis::suite());
  runner.addTest(TestMCCHDWangLandau::suite());


  CppUnit::BriefTestProgressListener listener;
  runner.eventManager().addListener(&listener);

  runner.run();

  return 0;
}
