// -*- coding: utf-8; -*-
/*!
 * 
 * \file HardDiscs.cpp
 * \brief Hard discs implementation
 * 
 * 
 * 
 * \author Johannes Knauf
 */



#ifdef HARDDISKS_HPP

#include <cmath>

namespace mcchd
{
  template<class RandomNumberGenerator, class CollisionFunctor>
  HardDiscs<RandomNumberGenerator, CollisionFunctor>::HardDiscs() : simulation_time(0)
  {
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  HardDiscs<RandomNumberGenerator, CollisionFunctor>::HardDiscs(const coordinate_type& new_extents) : container(new_extents), disc_table(new_extents), simulation_time(0)
  {
    extents = new_extents;

    volume = (extents[0] * extents[1] * extents[2]);
    double close_packing_fraction = M_PIl / 3. / sqrt(2.);
    double max_occupied_volume = volume * close_packing_fraction;
    double sphere_volume = M_PIl * 4. / 3. * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS;
    disc_id_type max_discs = static_cast<disc_id_type> (ceil(max_occupied_volume / sphere_volume));
    for (disc_id_type disc_id = 0; disc_id < max_discs; disc_id++)
      {
	all_discs.push_back(new Disc(disc_id));
      }

    num_present = 0; /// initial configuration: no disc present at start
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  HardDiscs<RandomNumberGenerator, CollisionFunctor>::~HardDiscs()
  {
    while(!all_discs.empty())
      {
	delete all_discs.back();
	all_discs.pop_back();
      }
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  coordinate_type HardDiscs<RandomNumberGenerator, CollisionFunctor>::get_extents() const
  {
    return extents;
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  const disc_id_type& HardDiscs<RandomNumberGenerator, CollisionFunctor>::get_number_of_discs() const
  {
    return num_present;
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  double HardDiscs<RandomNumberGenerator, CollisionFunctor>::energy() const
  {
    return num_present;
  }  

  template<class RandomNumberGenerator, class CollisionFunctor>
  const time_type& HardDiscs<RandomNumberGenerator, CollisionFunctor>::get_simulation_time() const
  {
    return simulation_time;
  }  

  template<class RandomNumberGenerator, class CollisionFunctor>
  const double& HardDiscs<RandomNumberGenerator, CollisionFunctor>::get_volume() const
  {
    return volume;
  }  

  template<class RandomNumberGenerator, class CollisionFunctor>
  bool HardDiscs<RandomNumberGenerator, CollisionFunctor>::is_overlapping(const Disc& test_disc)
  {
    bool collides_with_container = container.collides_with(test_disc);
    if (collides_with_container)
      return true;

    bool collides_with_other_disc = false;

    DiscVec neighbouring_discs = disc_table.get_neighbouring_discs(test_disc.get_center());
    for (DiscVec::const_iterator neighbour_cit = neighbouring_discs.begin(); neighbour_cit != neighbouring_discs.end(); neighbour_cit++)
      {
	if ((*neighbour_cit)->is_overlapping(test_disc, extents))
	  {
	    collides_with_other_disc = true;
	    break;
	  }
      }

    return collides_with_other_disc;
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  Step<RandomNumberGenerator, CollisionFunctor> HardDiscs<RandomNumberGenerator, CollisionFunctor>::propose_step(RandomNumberGenerator* rng)
  {
    const double insert_or_remove = rng->random_double();
    if (insert_or_remove < 0.5)
      {
	const Point random_center = Point(rng, extents);
	return Step<RandomNumberGenerator, CollisionFunctor>(this, random_center); /// insert constructor
      }
    else
      {
	const disc_id_type random_disc = rng->random_uint32(0, num_present ? num_present - 1 : 0); // num_present - 1 is included
	return Step<RandomNumberGenerator, CollisionFunctor>(this, random_disc); // remove constructor
      }
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  void HardDiscs<RandomNumberGenerator, CollisionFunctor>::commit(Step<RandomNumberGenerator, CollisionFunctor>& step_to_commit)
  {
    if (step_to_commit.is_remove_step())
      {
	this->remove_disc(step_to_commit.get_removal_idx());
      }
    else // insert step
      {
	this->insert_disc(step_to_commit.get_insert_coors());
      }
    simulation_time += 1;
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  void HardDiscs<RandomNumberGenerator, CollisionFunctor>::remove_disc(const disc_id_type& disc_idx)
  {
    Disc* const to_be_removed = all_discs[disc_idx];
    Disc* const last_disc = all_discs[num_present-1];
    
    all_discs[disc_idx] = last_disc;
    all_discs[num_present-1] = to_be_removed;
    num_present -= 1;

    disc_table.remove_disc(to_be_removed);
  }

  template<class RandomNumberGenerator, class CollisionFunctor>
  void HardDiscs<RandomNumberGenerator, CollisionFunctor>::insert_disc(const Point& new_coors)
  {
    Disc* const first_unused_disc = all_discs[num_present];
    first_unused_disc->translate_to(new_coors);
    num_present += 1;
    
    disc_table.insert_disc(first_unused_disc);
  }
}

#endif
