// -*- coding: utf-8; -*-
/*!
 * 
 * \file test_mcchd_WangLandau.cpp
 * \brief Wang Landau simulation implementation as a test case
 * 
 * The following tests are performed:
 *  - run a simple Wang Landau simulation; compare resulting density of states with presampled version
 * 
 * \author Johannes Knauf
 */

#include "test_mcchd_WangLandau.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

CppUnit::Test* TestMCCHDWangLandau::suite()
{
  CppUnit::TestSuite* suite_of_tests = new CppUnit::TestSuite("TestMCCHDWangLandau");
  suite_of_tests->addTest( new CppUnit::TestCaller<TestMCCHDWangLandau>("Mocasinns Wang Landau: interface compatibility and integration", &TestMCCHDWangLandau::test_wanglandau) );
  
  return suite_of_tests;
}

void TestMCCHDWangLandau::setUp()
{
  mcchd::coordinate_type extents = {{7.,7.,7.}};
  test_configuration = new ConfigurationType(extents);

  parameters.modification_factor_initial = 1.0;
  parameters.modification_factor_final = 1e-15;
  parameters.modification_factor_multiplier = 0.5;
  parameters.flatness = 0.6;
  parameters.sweep_steps = 10000;
  parameters.energy_cutoff_use = true;
  parameters.energy_cutoff = 50;

  test_simulation = new SimulationType(parameters, test_configuration);

  // result_comparison was generated with seed 1, 1e0 -- 1e-15, *0.5, =0.6, #10000, Emax 50
  result_comparison.push_back(0);
  result_comparison.push_back(6.495874713975656078446263563819229602813720703125);
  result_comparison.push_back(12.2557227848638348177701118402183055877685546875);
  result_comparison.push_back(17.606008685719661599478058633394539356231689453125);
  result_comparison.push_back(22.661528979123456650768275721929967403411865234375);
  result_comparison.push_back(27.479455081366179314272812916897237300872802734375);
  result_comparison.push_back(32.1110467496950064969496452249586582183837890625);
  result_comparison.push_back(36.58604914314111056228284724056720733642578125);
  result_comparison.push_back(40.914884743404712708070292137563228607177734375);
  result_comparison.push_back(45.0775249177071373196667991578578948974609375);
  result_comparison.push_back(49.1397478781945125092533999122679233551025390625);
  result_comparison.push_back(53.131490410988448047646670602262020111083984375);
  result_comparison.push_back(57.0265414772788830077843158505856990814208984375);
  result_comparison.push_back(60.77334388313914814716554246842861175537109375);
  result_comparison.push_back(64.4791258103715421157176024280488491058349609375);
  result_comparison.push_back(68.0839174650381124820341938175261020660400390625);
  result_comparison.push_back(71.5863722835517677367533906362950801849365234375);
  result_comparison.push_back(75.0615685076679284293277305550873279571533203125);
  result_comparison.push_back(78.4385543180066946433726116083562374114990234375);
  result_comparison.push_back(81.7155145809685308222469757311046123504638671875);
  result_comparison.push_back(84.9858574362982466254834434948861598968505859375);
  result_comparison.push_back(88.1782691155656124237793846987187862396240234375);
  result_comparison.push_back(91.3495277498420108486243407242000102996826171875);
  result_comparison.push_back(94.3694621224325800312726642005145549774169921875);
  result_comparison.push_back(97.4196299805365839574733399786055088043212890625);
  result_comparison.push_back(100.3879585425491285377574968151748180389404296875);
  result_comparison.push_back(103.2530682278201794588312623091042041778564453125);
  result_comparison.push_back(106.1038952303421893930135411210358142852783203125);
  result_comparison.push_back(108.9142737435852978933326085098087787628173828125);
  result_comparison.push_back(111.6673809958147529641792061738669872283935546875);
  result_comparison.push_back(114.3825406157888693314816919155418872833251953125);
  result_comparison.push_back(117.0444196998240471430108300410211086273193359375);
  result_comparison.push_back(119.6871711532486557416632422246038913726806640625);
  result_comparison.push_back(122.2758922931819398627339978702366352081298828125);
  result_comparison.push_back(124.8051334469966349161040852777659893035888671875);
  result_comparison.push_back(127.3051953623294849649028037674725055694580078125);
  result_comparison.push_back(129.767596963456497860534000210464000701904296875);
  result_comparison.push_back(132.096016092264591179628041572868824005126953125);
  result_comparison.push_back(134.362402638003544552702805958688259124755859375);
  result_comparison.push_back(136.629138314668722387068555690348148345947265625);
  result_comparison.push_back(138.904460980231277744678664021193981170654296875);
  result_comparison.push_back(141.158418856923475459552719257771968841552734375);
  result_comparison.push_back(143.296290689565040565867093391716480255126953125);
  result_comparison.push_back(145.357705584803710507912910543382167816162109375);
  result_comparison.push_back(147.501535447464419803509372286498546600341796875);
  result_comparison.push_back(149.467927727465024645425728522241115570068359375);
  result_comparison.push_back(151.467698321691301543978624977171421051025390625);
  result_comparison.push_back(153.466479826853770873640314675867557525634765625);
  result_comparison.push_back(155.439415981396422239413368515670299530029296875);
  result_comparison.push_back(157.465758854737003957779961638152599334716796875);
  result_comparison.push_back(159.361817362946823095626314170658588409423828125);
}

void TestMCCHDWangLandau::tearDown()
{
  delete test_configuration;
  delete test_simulation;
}

void TestMCCHDWangLandau::test_wanglandau()
{
  test_simulation->set_random_seed(2);

  test_simulation->do_wang_landau_simulation();

  Mocasinns::Histograms::Histocrete<energy_type, double> entropy_estimation = test_simulation->get_density_of_states();
  for (Mocasinns::Histograms::Histocrete<energy_type, double>::iterator ent_it = entropy_estimation.begin(); ent_it != entropy_estimation.end(); ent_it++)
    {
      const energy_type energy = (*ent_it).first;
      const double entropy = (*ent_it).second;
      const double expected = result_comparison[energy];
      // std::cout << "  result_comparison.push_back(" << std::setprecision(100) << entropy << ");" << std::endl;
      CPPUNIT_ASSERT((expected == 0. && entropy == 0.) || (abs(entropy - expected) < expected/1000.)); // test if precise to +- 0.1%
    }
}
