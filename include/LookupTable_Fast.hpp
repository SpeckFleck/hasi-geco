// -*- coding: utf-8; -*-
/*!
 * 
 * \file LookupTable_Fast.hpp
 * \brief Lookup table header -- fast version
 * 
 * Pure helper class for HardDiscs implementarion
 * 
 * \author Johannes Knauf
 */

#ifndef LOOKUPTABLE_FAST_HPP
#define LOOKUPTABLE_FAST_HPP

#include <vector>

#include <boost/array.hpp>
#include <boost/multi_array.hpp>

#include <Point.hpp>
#include <Disc.hpp>
#include <mcchd_typedefs.hpp>

namespace mcchd {

  class LookupTable_Fast
  {
  private:
    coordinate_type extents;
    coordinate_type cell_scale;
    multi_index_type num_cells;
    Cells3D* space_cells;

    multi_index_type get_cell_idx(const Point&) const;
  public:
    LookupTable_Fast();
    LookupTable_Fast(const coordinate_type&);
    ~LookupTable_Fast();
    DiscVec get_neighbouring_discs(const Point&) const;
    void remove_disc(Disc* const);
    void insert_disc(Disc* const);
  };

}

#include <LookupTable_Fast.cpp>

#endif
