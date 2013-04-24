// -*- coding: utf-8; -*-
/*!
 * 
 * \file Step.cpp
 * \brief Encapsulator of step data -- implementation
 * 
 * 
 * 
 * \author Johannes Knauf
 */

#ifdef STEP_HPP

namespace mcchd
{
  /// move disc constructor
  template <class HardDiscSpace>
  Step<HardDiscSpace>::Step(HardDiscSpace* const configuration, const disc_id_type& disc_idx, const Point& displacement) : hard_disc_configuration_space(configuration)
  {
    is_move = true;
    to_be_removed = disc_idx;
    target_coor = displacement;
  }

  /// remove disc constructor
  template <class HardDiscSpace>
  Step<HardDiscSpace>::Step(HardDiscSpace* const configuration, const disc_id_type& disc_idx) : hard_disc_configuration_space(configuration)
  {
    is_move = false;
    is_remove = true;
    to_be_removed = disc_idx;
  }

  /// insert disc constructor
  template <class HardDiscSpace>
  Step<HardDiscSpace>::Step(HardDiscSpace* const configuration, const Point& place_here) : hard_disc_configuration_space(configuration)
  {
    is_move = false;
    is_remove = false;
    target_coor = place_here;
  }

  template <class HardDiscSpace>
  Step<HardDiscSpace>::~Step()
  {
  }

  template <class HardDiscSpace>
  time_type Step<HardDiscSpace>::get_creation_simulation_time() const
  {
    return creation_simulation_time;
  }

  template <class HardDiscSpace>
  int Step<HardDiscSpace>::delta_E() const
  {
    if (is_move)
      return 0;
    else if (is_remove)
      return -1;
    else
      return 1;
  }

  template <class HardDiscSpace>
  bool Step<HardDiscSpace>::is_executable() const
  {
    if (is_move)
      return (hard_disc_configuration_space->get_number_of_discs() > 0) && (! hard_disc_configuration_space->is_overlapping_after_displacement(to_be_removed, target_coor));
    if (is_remove)
      return hard_disc_configuration_space->get_number_of_discs() > 0;
    else
      return (! hard_disc_configuration_space->is_overlapping(Disc(target_coor, -1))); // -1 is unused test disc id
  }

  template <class HardDiscSpace>
  bool Step<HardDiscSpace>::is_move_step() const
  {
    return is_move;
  }

  template <class HardDiscSpace>
  bool Step<HardDiscSpace>::is_remove_step() const
  {
    return is_remove;
  }

  template <class HardDiscSpace>
  disc_id_type Step<HardDiscSpace>::get_removal_idx() const
  {
    return to_be_removed;
  }

  template <class HardDiscSpace>
  Point Step<HardDiscSpace>::get_insert_coors() const
  {
    return target_coor;
  }

  template <class HardDiscSpace>
  void Step<HardDiscSpace>::execute()
  {
    hard_disc_configuration_space->commit(*this);
  }

  template <class HardDiscSpace>
  double Step<HardDiscSpace>::selection_probability_factor() const
  {
    const double num_discs = static_cast<double> (hard_disc_configuration_space->get_number_of_discs());
    const double volume = hard_disc_configuration_space->get_volume();
    const double sphere_volume = M_PI * 4. / 3. * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS;
    const double thermal_wavelength_pow_3 = sphere_volume;
    const double pre_factor_VL3 = volume / thermal_wavelength_pow_3;

    if (is_move)
      return 1.;
    if (is_remove)
      return pre_factor_VL3 / num_discs;
    else
      return (num_discs + 1.) / pre_factor_VL3;
  }


}


#endif
