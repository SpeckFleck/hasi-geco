// -*- coding: utf-8; -*-
/*!
 * 
 * \file CollisionFunctor_SingularDefects.hpp
 * \brief Prototype example of a CollisionFunctor
 * 
 * Contains the following containers:
 *  - bulk -- no boundaries
 *  - bulk with point defect -- a forbidden point in the center of the box
 *  - bulk with line defect -- a forbidden line in the center of the box in the xy-plane
 *  - bulk with plane defect -- a forbidden plane in the center of the box in x-direction
 * 
 * \author Johannes Knauf
 */

#ifndef COLLISIONFUNCTOR_SINGULARDEFECTS_HPP
#define COLLISIONFUNCTOR_SINGULARDEFECTS_HPP

#include <Point.hpp>
#include <Disc.hpp>

namespace mcchd {

  class CF_Bulk {
  private:
    coordinate_type extents;
    Point center;
  public:
    CF_Bulk();
    CF_Bulk(const coordinate_type&);
    ~CF_Bulk();
    bool collides_with(const Disc&) const;
  };

  class CF_PointDefect {
  private:
    coordinate_type extents;
    Point center;
  public:
    CF_PointDefect();
    CF_PointDefect(const coordinate_type&);
    ~CF_PointDefect();
    bool collides_with(const Disc&) const;
  };

  class CF_LineDefect {
  private:
    coordinate_type extents;
    Point center;
  public:
    CF_LineDefect();
    CF_LineDefect(const coordinate_type&);
    ~CF_LineDefect();
    bool collides_with(const Disc&) const;
  };

  class CF_PlaneDefect {
  private:
    coordinate_type extents;
    Point center;
  public:
    CF_PlaneDefect();
    CF_PlaneDefect(const coordinate_type&);
    ~CF_PlaneDefect();
    bool collides_with(const Disc&) const;
  };

}

#include <CollisionFunctor_SingularDefects.cpp>

#endif
