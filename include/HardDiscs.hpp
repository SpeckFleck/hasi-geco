// -*- coding: utf-8; -*-
/*!
 * 
 * \file HardDiscs.hpp
 * \brief Hard Discs header
 * 
 * Provides energy() interface for Mocasinns.
 * Provides propose_step() interface for Mocasinns.
 * Provides get_simulation_time() interface for Mocasinns SimulationStatus() watcher.
 * 
 * Provides commit() interface for Step class.
 *
 * Contains LookupTable for fast overlap checks.
 * Contains CollisionFunctor for overlap checks with boundary.
 * 
 * \author Johannes Knauf
 */

#ifndef HARDDISKS_HPP
#define HARDDISKS_HPP

#include <cstdint>
#include <vector>

#include <Step.hpp>
#include <Point.hpp>
#include <Disc.hpp>
#include <LookupTable_Fast.hpp>
// #include <LookupTable_Brute.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <mcchd_typedefs.hpp>


namespace mcchd {

  typedef LookupTable_Fast LookupTable;
  // typedef LookupTable_Brute LookupTable;

  template<class CollisionFunctor>
  class HardDiscs {
  private:
    CollisionFunctor container;
    /// all_discs is divided in 2 halves: 
    ///  1st half (til idx == num_present): Disc is in the system
    ///  2nd half (including and above idx == num_present): Disc is out of the system
    DiscCollection all_discs; 
    disc_id_type num_present;
    LookupTable disc_table;
    coordinate_type extents;
    double volume;
    time_type simulation_time;

  public:
    HardDiscs();
    HardDiscs(const coordinate_type& extents);
    ~HardDiscs();
    const disc_id_type& get_number_of_discs() const;
    coordinate_type get_extents() const;
    energy_type energy() const;
    const time_type& get_simulation_time() const;
    const double& get_volume() const;
    bool is_overlapping(const Disc&);
    template <class RandomNumberGenerator> Step<HardDiscs<CollisionFunctor> > propose_step(RandomNumberGenerator*);
    void commit(Step<HardDiscs<CollisionFunctor> >&);
    void remove_disc(const disc_id_type&);
    void insert_disc(const Point&);

    template<class Archive> void serialize(Archive & ar, const unsigned int)
    {
      ar & num_present;
    }
  };

}


#include "HardDiscs.cpp"

#endif
