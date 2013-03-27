// -*- coding: utf-8; -*-
/*!
 * 
 * \file mcchd_typedefs.hpp
 * \brief Cluster all type definitions
 * 
 * 
 * 
 * \author Johannes Knauf
 */

#ifndef MCCHD_TYPEDEFS_HPP
#define MCCHD_TYPEDEFS_HPP

#include <vector>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>

#include <Point.hpp>
#include <Disc.hpp>

namespace mcchd
{
  const int dimensions = 3;

  typedef boost::multi_array<Disc*, dimensions> Cells3D;
  typedef std::vector<const Disc*> DiscVec;
  typedef boost::multi_array_types::index index_type;
  typedef boost::array<index_type, dimensions> multi_index_type;

  typedef std::vector<Disc*> DiscCollection;
  typedef uint64_t time_type;
  typedef int energy_type;

}


#endif
