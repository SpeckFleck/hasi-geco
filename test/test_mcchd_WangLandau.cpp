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
  result_comparison.push_back(6.4179794670059227001956969616003334522247314453125);
  result_comparison.push_back(12.187266895781906583806630806066095829010009765625);
  result_comparison.push_back(17.568939636472833853986230678856372833251953125);
  result_comparison.push_back(22.66575308165062097032205201685428619384765625);
  result_comparison.push_back(27.5069348572777698791469447314739227294921875);
  result_comparison.push_back(32.14108898656031243490360793657600879669189453125);
  result_comparison.push_back(36.57824385738219774566459818743169307708740234375);
  result_comparison.push_back(40.88649646014857097497952054254710674285888671875);
  result_comparison.push_back(45.09669660774410004933088202960789203643798828125);
  result_comparison.push_back(49.17754400859283947511357837356626987457275390625);
  result_comparison.push_back(53.10962855325808362749739899300038814544677734375);
  result_comparison.push_back(56.98466682854382980849550222046673297882080078125);
  result_comparison.push_back(60.78952625715312052534500253386795520782470703125);
  result_comparison.push_back(64.48493992964864673922420479357242584228515625);
  result_comparison.push_back(68.113925687825116028761840425431728363037109375);
  result_comparison.push_back(71.669050540176300501116202212870121002197265625);
  result_comparison.push_back(75.1074531917455487928236834704875946044921875);
  result_comparison.push_back(78.472338412040045341200311668217182159423828125);
  result_comparison.push_back(81.828639630264007109872181899845600128173828125);
  result_comparison.push_back(85.146188945238037604212877340614795684814453125);
  result_comparison.push_back(88.341179565077283086793613620102405548095703125);
  result_comparison.push_back(91.53923804171387246242375113070011138916015625);
  result_comparison.push_back(94.619522959294243946715141646564006805419921875);
  result_comparison.push_back(97.658006401151027375817648135125637054443359375);
  result_comparison.push_back(100.736730300881191624284838326275348663330078125);
  result_comparison.push_back(103.69983665172804876419831998646259307861328125);
  result_comparison.push_back(106.598989509194467473207623697817325592041015625);
  result_comparison.push_back(109.430986667186886052149930037558078765869140625);
  result_comparison.push_back(112.211875824838131165961385704576969146728515625);
  result_comparison.push_back(114.937866818078674668868188746273517608642578125);
  result_comparison.push_back(117.675612083847596522900857962667942047119140625);
  result_comparison.push_back(120.32839663203532154511776752769947052001953125);
  result_comparison.push_back(122.9423320685285716535872779786586761474609375);
  result_comparison.push_back(125.465077887852515914346440695226192474365234375);
  result_comparison.push_back(128.01359738887998673817492090165615081787109375);
  result_comparison.push_back(130.480471989274747102172113955020904541015625);
  result_comparison.push_back(132.9494961320118591174832545220851898193359375);
  result_comparison.push_back(135.3044302782221848246990703046321868896484375);
  result_comparison.push_back(137.61674594077641131661948747932910919189453125);
  result_comparison.push_back(139.9912677011352570843882858753204345703125);
  result_comparison.push_back(142.35314557933139667511568404734134674072265625);
  result_comparison.push_back(144.6307838127828517826856113970279693603515625);
  result_comparison.push_back(146.84266689174609155088546685874462127685546875);
  result_comparison.push_back(149.04649177081631705732434056699275970458984375);
  result_comparison.push_back(151.17559117986598948846221901476383209228515625);
  result_comparison.push_back(153.25824380263640023258631117641925811767578125);
  result_comparison.push_back(155.31450695471249900947441346943378448486328125);
  result_comparison.push_back(157.32916756915841460795491002500057220458984375);
  result_comparison.push_back(159.35514602136800021980889141559600830078125);
  result_comparison.push_back(161.33108074738646564583177678287029266357421875);
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
