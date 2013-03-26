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
  /// insert disc constructor
  template <class CollisionFunctor>
  Step<CollisionFunctor>::Step(HardDiscs<CollisionFunctor>* const configuration, const Point& place_here) : hard_disc_configuration_space(configuration)
  {
    is_remove = false;
    target_coor = place_here;
  }

  /// remove disc constructor
  template <class CollisionFunctor>
  Step<CollisionFunctor>::Step(HardDiscs<CollisionFunctor>* const configuration, const disc_id_type& disc_idx) : hard_disc_configuration_space(configuration)
  {
    is_remove = true;
    to_be_removed = disc_idx;
  }

  template <class CollisionFunctor>
  Step<CollisionFunctor>::~Step()
  {
  }

  template <class CollisionFunctor>
  int Step<CollisionFunctor>::get_creation_simulation_time() const
  {
    return creation_simulation_time;
  }

  template <class CollisionFunctor>
  int Step<CollisionFunctor>::delta_E() const
  {
    if (is_remove)
      return -1;
    else
      return 1;
  }

  template <class CollisionFunctor>
  bool Step<CollisionFunctor>::is_executable() const
  {
    if (is_remove)
      return hard_disc_configuration_space->get_number_of_discs() > 0;
    else
      return (! hard_disc_configuration_space->is_overlapping(Disc(target_coor, 1)));
  }

  template <class CollisionFunctor>
  bool Step<CollisionFunctor>::is_remove_step() const
  {
    return is_remove;
  }

  template <class CollisionFunctor>
  disc_id_type Step<CollisionFunctor>::get_removal_idx() const
  {
    return to_be_removed;
  }

  template <class CollisionFunctor>
  Point Step<CollisionFunctor>::get_insert_coors() const
  {
    return target_coor;
  }

  template <class CollisionFunctor>
  void Step<CollisionFunctor>::execute()
  {
    hard_disc_configuration_space->commit(*this);
  }

  template <class CollisionFunctor>
  double Step<CollisionFunctor>::selection_probability_factor() const
  {
    const double num_discs = static_cast<double> (hard_disc_configuration_space->get_number_of_discs());
    const double volume = hard_disc_configuration_space->get_volume();
    const double sphere_volume = M_PI * 4. / 3. * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS;
    const double thermal_wavelength_pow_3 = sphere_volume;
    const double pre_factor_VL3 = volume / thermal_wavelength_pow_3;

    if (is_remove)
      return pre_factor_VL3 / num_discs;
    else
      return (num_discs + 1.) / pre_factor_VL3;
  }


}


#endif
