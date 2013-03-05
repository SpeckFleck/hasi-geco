// -*- coding: utf-8; -*-
/*!
 * 
 * \file LookupTable.cpp
 * \brief Lookup Table for Discs in periodic space -- implementation
 * 
 * TBD: More efficient structure with smaller cell size (R=0.5 guarantees 1 Disc per cell only)
 * 
 * \author Johannes Knauf
 */

#ifdef LOOKUPTABLE_HPP

#include <cmath>

namespace mcchd {

  inline multi_index_type LookupTable::get_cell_idx(const Point& point) const
  {
    multi_index_type multi_idx;
    multi_idx[0] = static_cast<index_type> (floor(fmod(point.get_coor(0), extents[0]) / cell_scale[0]));
    multi_idx[1] = static_cast<index_type> (floor(fmod(point.get_coor(1), extents[1]) / cell_scale[1]));
    multi_idx[2] = static_cast<index_type> (floor(fmod(point.get_coor(2), extents[2]) / cell_scale[2]));

    return multi_idx;
  }

  inline CellVec LookupTable::get_surrounding_cells(const Point& point) const
  {
    CellVec surrounding_cells;
    multi_index_type multi_idx = get_cell_idx(point);
    for (int i = -1; i <= 1; i++)
      {
	index_type i_idx = (multi_idx[0] + i) % num_cells[0];
	for (int j = -1; j <= 1; j++)
	  {
	    index_type j_idx = (multi_idx[1] + j) % num_cells[1];
	    for (int k = -1; k <= 1; k++)
	      {
		index_type k_idx = (multi_idx[2] + k) % num_cells[2];
		
		const Cell* found_cell = &((*space_cells)[i_idx][j_idx][k_idx]);
		surrounding_cells.push_back(found_cell);
	      }	    
	  }
      }

    return surrounding_cells;
  }

  inline LookupTable::LookupTable()
  {
  }

  inline LookupTable::LookupTable(const coordinate_type& new_extents)
  {
    extents = new_extents;
    double base_scale = 2 * DEFAULT_DISC_RADIUS;
    num_cells = multi_index_type();
    num_cells[0] = static_cast<index_type> (ceil(new_extents[0] / base_scale));
    num_cells[1] = static_cast<index_type> (ceil(new_extents[1] / base_scale));
    num_cells[2] = static_cast<index_type> (ceil(new_extents[2] / base_scale));
    cell_scale[0] = new_extents[0] / num_cells[0];
    cell_scale[1] = new_extents[1] / num_cells[1];
    cell_scale[2] = new_extents[2] / num_cells[2];

    space_cells = new Cells3D(boost::extents[num_cells[0]][num_cells[1]][num_cells[2]]);
  }

  inline LookupTable::~LookupTable()
  {
  }

  inline DiscVec LookupTable::get_neighbouring_discs(const Point& around_point) const
  {
    DiscVec neighbouring_discs;
    const CellVec surrounding_cells = get_surrounding_cells(around_point);
    for (CellVec::const_iterator sc_it = surrounding_cells.begin(); sc_it != surrounding_cells.end(); sc_it++)
      {
	for (Cell::const_iterator c_it = (*sc_it)->begin(); c_it != (*sc_it)->end(); c_it++)
	  {
	    const Disc* found_disc = (*c_it);

	    if (found_disc != NULL)
	      neighbouring_discs.push_back(found_disc);
	  }
      }

    return neighbouring_discs;
  }

  inline void LookupTable::remove_disc(Disc* const disc_to_be_removed)
  {
    const multi_index_type cell_idx = get_cell_idx(disc_to_be_removed->get_center());
    /// does not check, if disc is where it should be or exists as duplicate or ...
    /// Always check this elsewhere!

    Cell* target_cell = &((*space_cells)[cell_idx[0]][cell_idx[1]][cell_idx[2]]);
    for (Cell::iterator c_it = target_cell->begin(); c_it != target_cell->end(); c_it++)
      {
        if ((*c_it) == disc_to_be_removed)
	  {
	    *c_it = NULL;
	    break;
	  }
      }
  }

  inline void LookupTable::insert_disc(Disc* const disc_to_be_inserted)
  {
    const multi_index_type cell_idx = get_cell_idx(disc_to_be_inserted->get_center());
    /// does not check, if collision happens
    /// Always check this elsewhere!

    Cell* target_cell = &((*space_cells)[cell_idx[0]][cell_idx[1]][cell_idx[2]]);
    for (Cell::iterator c_it = target_cell->begin(); c_it != target_cell->end(); c_it++)
      {
	if ((*c_it) == NULL)
	  {
	    *c_it = disc_to_be_inserted;
	    break;
	  }
      }
  }

}

#endif
