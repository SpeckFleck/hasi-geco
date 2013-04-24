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

#include <mcchd_typedefs.hpp>

namespace mcchd
{

  const double max_move_size_multiplier = 0.2;
  const double max_move_size = max_move_size_multiplier * DEFAULT_DISC_RADIUS;
  const coordinate_type max_displacement_boundaries = {{2. * max_move_size, 2. * max_move_size, 2. * max_move_size}};

  const double P_move = 1./3.;
  // remove and insert share equal parts of the remaining probability
  const double P_remove_threshold = 1./2. + P_move/2.;
  // P_insert_threshold = 1.

  template<class HardDiscSpace>
  class Step {
  private:
    HardDiscSpace* const hard_disc_configuration_space;
    disc_id_type to_be_removed;
    Point target_coor;
    time_type creation_simulation_time;
    bool is_move;
    bool is_remove; /// if not remove, insert
  public:
    Step(HardDiscSpace* const, const disc_id_type&, const Point&); /// move
    Step(HardDiscSpace* const, const disc_id_type&); /// remove
    Step(HardDiscSpace* const, const Point&); /// insert 
    ~Step();
    Disc get_old_spin() const;
    Disc get_new_spin() const;
    time_type get_creation_simulation_time() const;
    energy_type delta_E() const;
    bool is_executable() const;
    bool is_move_step() const;
    bool is_remove_step() const;
    // move_step?
    void execute();
    disc_id_type get_removal_idx() const;
    Point get_insert_coors() const;
    double selection_probability_factor() const;
  };

}

#include <Step.cpp>

#endif
