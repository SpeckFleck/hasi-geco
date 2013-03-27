// -*- coding: utf-8; -*-
/*!
 * 
 * \file LookupTable_Brute.cpp
 * \brief Lookup Table for Discs in periodic space -- brute force super-slow implementation
 * 
 * \author Johannes Knauf
 */

#ifdef LOOKUPTABLE_HPP

#include <algorithm>

#include <cassert>
#include <cmath>

namespace mcchd {

  inline LookupTable_Brute::LookupTable_Brute()
  {
  }

  inline LookupTable_Brute::LookupTable_Brute(const coordinate_type& new_extents)
  {
    extents = new_extents;

    // BEWARE: Code duplication!
    extents = new_extents;
    const double volume = (extents[0] * extents[1] * extents[2]);

    const double close_packing_fraction = M_PI / 3. / sqrt(2.);
    const double max_occupied_volume = volume * close_packing_fraction;
    const double sphere_volume = M_PI * 4. / 3. * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS * DEFAULT_DISC_RADIUS;
    const disc_id_type max_discs = static_cast<disc_id_type> (ceil(max_occupied_volume / sphere_volume));
    for (disc_id_type disc_id = 0; disc_id < max_discs; disc_id++)
      {
	all_discs_mirror.push_back(NULL);
      }

    num_present = 0; /// initial configuration: no disc present at start
  }

  inline LookupTable_Brute::~LookupTable_Brute()
  {
  }

  inline DiscVec LookupTable_Brute::get_neighbouring_discs(const Point&) const
  {
    DiscVec neighbouring_discs;

    for (disc_id_type disc_id = 0; disc_id < num_present; disc_id++)
      {
	neighbouring_discs.push_back(all_discs_mirror[disc_id]);
      }

    return neighbouring_discs;
  }

  inline void LookupTable_Brute::remove_disc(Disc* const disc_to_be_removed)
  {
    for (disc_id_type disc_id = 0; disc_id < num_present; disc_id++)
      {
	if (all_discs_mirror[disc_id] == disc_to_be_removed)
	  {
	    Disc* const to_be_removed = all_discs_mirror[disc_id];
	    Disc* const last_disc = all_discs_mirror[num_present-1];

	    all_discs_mirror[disc_id] = last_disc;
	    all_discs_mirror[num_present-1] = to_be_removed;
	    num_present -= 1;
	  }
      }
  }

  inline void LookupTable_Brute::insert_disc(Disc* const disc_to_be_inserted)
  {
    all_discs_mirror[num_present] = disc_to_be_inserted;
    num_present += 1;
  }

}

#endif
