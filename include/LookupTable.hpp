// -*- coding: utf-8; -*-
/*!
 * 
 * \file LookupTable.hpp
 * \brief Lookup table header
 * 
 * Pure helper class for HardDiscs implementarion
 * 
 * \author Johannes Knauf
 */

#ifndef LOOKUPTABLE_HPP
#define LOOKUPTABLE_HPP

#include <array>
#include <vector>

#include <boost/multi_array.hpp>

#include <Point.hpp>
#include <Disc.hpp>

namespace mcchd {

  typedef std::array<Disc*, 8> Cell;
  typedef boost::multi_array<Cell, 3> Cells3D;
  typedef std::vector<const Cell*> CellVec;
  typedef std::vector<const Disc*> DiscVec;
  typedef boost::multi_array_types::size_type index_type;
  typedef std::array<index_type, 3> multi_index_type;

  class LookupTable
  {
  private:
    coordinate_type extents;
    coordinate_type cell_scale;
    multi_index_type num_cells;
    Cells3D* space_cells;

    multi_index_type get_cell_idx(const Point&) const;
    CellVec get_surrounding_cells(const Point&) const;
  public:
    LookupTable();
    LookupTable(const coordinate_type&);
    ~LookupTable();
    DiscVec get_neighbouring_discs(const Point&) const;
    void remove_disc(Disc* const);
    void insert_disc(Disc* const);
  };

}

#include <LookupTable.cpp>

#endif
