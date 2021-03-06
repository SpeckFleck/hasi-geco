// -*- coding: utf-8; -*-
/*!
 * 
 * \file LookupTable_Fast.cpp
 * \brief Lookup Table for Discs in periodic space -- fast version implementation
 * 
 * \author Johannes Knauf
 */

#ifdef LOOKUPTABLE_FAST_HPP

#include <algorithm>

#include <cassert>
#include <cmath>

namespace mcchd {

  inline multi_index_type LookupTable_Fast::get_cell_idx(const Point& point) const
  {
    multi_index_type point_idx;
    point_idx[0] = static_cast<index_type> (floor(fmod(point.get_coor(0), extents[0]) / cell_scale[0]));
    point_idx[1] = static_cast<index_type> (floor(fmod(point.get_coor(1), extents[1]) / cell_scale[1]));
    point_idx[2] = static_cast<index_type> (floor(fmod(point.get_coor(2), extents[2]) / cell_scale[2]));

    return point_idx;
  }

  inline LookupTable_Fast::LookupTable_Fast()
  {
  }

  inline LookupTable_Fast::LookupTable_Fast(const coordinate_type& new_extents)
  {
    extents = new_extents;
    const double base_scale = 2 * DEFAULT_DISC_RADIUS;
    const double cell_width_max = base_scale / sqrt(dimensions); // guarantees only 1 disc per box
    num_cells[0] = static_cast<index_type> (ceil(new_extents[0] / cell_width_max));
    num_cells[1] = static_cast<index_type> (ceil(new_extents[1] / cell_width_max));
    num_cells[2] = static_cast<index_type> (ceil(new_extents[2] / cell_width_max));
    cell_scale[0] = new_extents[0] / num_cells[0];
    cell_scale[1] = new_extents[1] / num_cells[1];
    cell_scale[2] = new_extents[2] / num_cells[2];

    space_cells = new Cells3D(boost::extents[num_cells[0]][num_cells[1]][num_cells[2]]);
    for (index_type i = 0; i < num_cells[0]; i++)
      {
	for (index_type j = 0; j < num_cells[1]; j++)
	  {
	    for (index_type k = 0; k < num_cells[2]; k++)
	      {
		((*space_cells)[i][j][k]) = NULL;
	      }
	  }
      }
  }

  inline LookupTable_Fast::~LookupTable_Fast()
  {
  }

  inline DiscVec LookupTable_Fast::get_neighbouring_discs(const Point& around_point) const
  {
    DiscVec neighbouring_discs;
    get_neighbouring_discs(around_point, neighbouring_discs);
    return neighbouring_discs;
  }

  inline void LookupTable_Fast::get_neighbouring_discs(const Point& around_point, DiscVec& neighbouring_discs) const
  {
    neighbouring_discs.clear();
    
    multi_index_type multi_idx = get_cell_idx(around_point);
    // using -2:2 is fuddled, for x_max < 4 it should be -3:3 to avoid collisions
    // make check at initializtion? change correspondingly?
    const int cell_range = 2;
    const int max_cells = 2 * cell_range + 1;
    boost::array<index_type, max_cells> i_idces, j_idces, k_idces;
    
    int cell = 0;
    for (int i = -cell_range; i <= cell_range; i++)
      {
	const index_type pre_i_idx = (multi_idx[0] + i);
	const index_type i_idx = pre_i_idx < 0 ? pre_i_idx + num_cells[0] : pre_i_idx >= num_cells[0] ? pre_i_idx - num_cells[0] : pre_i_idx;
	i_idces[cell] = i_idx;
	cell++;
      }

    cell = 0;
    for (int j = -cell_range; j <= cell_range; j++)
      {
	const index_type pre_j_idx = (multi_idx[1] + j);
	const index_type j_idx = pre_j_idx < 0 ? pre_j_idx + num_cells[1] : pre_j_idx >= num_cells[1] ? pre_j_idx - num_cells[1] : pre_j_idx;
	j_idces[cell] = j_idx;
	cell++;
      }

    cell = 0;
    for (int k = -cell_range; k <= cell_range; k++)
      {
	const index_type pre_k_idx = (multi_idx[2] + k);
	const index_type k_idx = pre_k_idx < 0 ? pre_k_idx + num_cells[2] : pre_k_idx >= num_cells[2] ? pre_k_idx - num_cells[2] : pre_k_idx;
	k_idces[cell] = k_idx;
	cell++;
      }

    for (int i = 0; i < max_cells; i++)
      {
	const index_type i_idx = i_idces[i];
	for (int j = 0; j < max_cells; j++)
	  {
	    const index_type j_idx = j_idces[j];
	    for (int k = 0; k < max_cells; k++)
	      {
		const index_type k_idx = k_idces[k];

		const Disc* found_disc = ((*space_cells)[i_idx][j_idx][k_idx]);
		
 		if (found_disc != NULL)
		  neighbouring_discs.push_back(found_disc);
	      }	    
	  }
      }
  }

  inline void LookupTable_Fast::remove_disc(Disc* const disc_to_be_removed)
  {
    const multi_index_type cell_idx = get_cell_idx(disc_to_be_removed->get_center());
    assert((*space_cells)(cell_idx) == disc_to_be_removed);
    (*space_cells)(cell_idx) = NULL;
  }

  inline void LookupTable_Fast::insert_disc(Disc* const disc_to_be_inserted)
  {
    const multi_index_type cell_idx = get_cell_idx(disc_to_be_inserted->get_center());
    assert((*space_cells)(cell_idx) == NULL);
    (*space_cells)(cell_idx) = disc_to_be_inserted;
  }

}

#endif
