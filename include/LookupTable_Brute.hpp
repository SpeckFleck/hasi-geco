// -*- coding: utf-8; -*-
/*!
 * 
 * \file LookupTable_Brute.hpp
 * \brief Lookup table header -- brute force super-slow
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
#include <mcchd_typedefs.hpp>

namespace mcchd {

  class LookupTable_Brute
  {
  private:
    coordinate_type extents;
    DiscCollection all_discs_mirror;
    disc_id_type num_present;

  public:
    LookupTable_Brute();
    LookupTable_Brute(const coordinate_type&);
    ~LookupTable_Brute();
    DiscVec get_neighbouring_discs(const Point&) const;
    void remove_disc(Disc* const);
    void insert_disc(Disc* const);
  };

}

#include <LookupTable_Brute.cpp>

#endif
