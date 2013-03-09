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

#include <vector>

#include <boost/array.hpp>
#include <boost/multi_array.hpp>

#include <Point.hpp>
#include <Disc.hpp>

namespace mcchd {

  const int dimensions = 3;

  typedef boost::multi_array<Disc*, dimensions> Cells3D;
  typedef std::vector<const Disc*> DiscVec;
  typedef boost::multi_array_types::size_type index_type;
  typedef boost::array<index_type, dimensions> multi_index_type;

  class LookupTable
  {
  private:
    coordinate_type extents;
    coordinate_type cell_scale;
    multi_index_type num_cells;
    Cells3D* space_cells;

    multi_index_type get_cell_idx(const Point&) const;
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
