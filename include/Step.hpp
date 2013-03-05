// -*- coding: utf-8; -*-
/*!
 * 
 * \file Step.hpp
 * \brief Encapsulator for step data
 * 
 * Provides is_executable() interface for Mocasinns.
 * Provides execute() interface for Mocasinns.
 * Provides delta_E() interface for Mocasinns.
 * Provides selection_probability_factor() interface for Mocasinns.
 * Provides get_creation_simulation_time() interface for Mocasinns SimulationStatus() watcher.
 *
 * Contains backreference to the originating HardDiscs configuration space.
 * 
 * \author Johannes Knauf
 */

#ifndef STEP_HPP
#define STEP_HPP

#include <Disc.hpp>
#include <Point.hpp>

namespace mcchd
{

  template <class, class> class HardDiscs;
  typedef uint64_t simulation_time_type;

  template<class RandomNumberGenerator, class CollisionFunctor>
  class Step {
  private:
    HardDiscs<RandomNumberGenerator, CollisionFunctor>* const hard_disc_configuration_space;
    disc_id_type to_be_removed;
    Point target_coor;
    simulation_time_type creation_simulation_time;
    bool is_remove; /// if not remove, insert
  public:
    Step(HardDiscs<RandomNumberGenerator, CollisionFunctor>* const, const Point&); /// insert 
    Step(HardDiscs<RandomNumberGenerator, CollisionFunctor>* const, const disc_id_type&); /// remove
    ~Step();
    Disc get_old_spin() const;
    Disc get_new_spin() const;
    int get_creation_simulation_time() const;
    int delta_E() const;
    bool is_executable() const;
    bool is_remove_step() const;
    void execute();
    disc_id_type get_removal_idx() const;
    Point get_insert_coors() const;
    double selection_probability_factor() const;
  };

}

#include <Step.cpp>

#endif
