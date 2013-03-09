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
  template <class RandomNumberGenerator, class CollisionFunctor>
  Step<RandomNumberGenerator, CollisionFunctor>::Step(HardDiscs<RandomNumberGenerator, CollisionFunctor>* const configuration, const Point& place_here) : hard_disc_configuration_space(configuration)
  {
    is_remove = false;
    target_coor = place_here;
  }

  /// remove disc constructor
  template <class RandomNumberGenerator, class CollisionFunctor>
  Step<RandomNumberGenerator, CollisionFunctor>::Step(HardDiscs<RandomNumberGenerator, CollisionFunctor>* const configuration, const disc_id_type& disc_idx) : hard_disc_configuration_space(configuration)
  {
    is_remove = true;
    to_be_removed = disc_idx;
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  Step<RandomNumberGenerator, CollisionFunctor>::~Step()
  {
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  int Step<RandomNumberGenerator, CollisionFunctor>::get_creation_simulation_time() const
  {
    return creation_simulation_time;
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  int Step<RandomNumberGenerator, CollisionFunctor>::delta_E() const
  {
    if (is_remove)
      return -1;
    else
      return 1;
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  bool Step<RandomNumberGenerator, CollisionFunctor>::is_executable() const
  {
    if (is_remove)
      return hard_disc_configuration_space->get_number_of_discs() > 0;
    else
      return (! hard_disc_configuration_space->is_overlapping(Disc(target_coor, 1)));
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  bool Step<RandomNumberGenerator, CollisionFunctor>::is_remove_step() const
  {
    return is_remove;
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  disc_id_type Step<RandomNumberGenerator, CollisionFunctor>::get_removal_idx() const
  {
    return to_be_removed;
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  Point Step<RandomNumberGenerator, CollisionFunctor>::get_insert_coors() const
  {
    return target_coor;
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  void Step<RandomNumberGenerator, CollisionFunctor>::execute()
  {
    hard_disc_configuration_space->commit(*this);
  }

  template <class RandomNumberGenerator, class CollisionFunctor>
  double Step<RandomNumberGenerator, CollisionFunctor>::selection_probability_factor() const
  {
    const disc_id_type num_discs = hard_disc_configuration_space->get_number_of_discs();
    const double volume = hard_disc_configuration_space->get_volume();
    const double thermal_wavelength_pow_3 = 1.;

    if (is_remove)
      return volume * thermal_wavelength_pow_3 / static_cast<double> (num_discs);
    else
      return static_cast<double> (num_discs+1) / volume / thermal_wavelength_pow_3;
  }


}


#endif
