// -*- coding: utf-8; -*-
/*!
 * 
 * \file CollisionFunctor_NodalSurfaces.hpp
 * \brief Collision functors modeling nodal surfaces -- header
 * 
 * Implements the surface types:
 *  - P
 *  - D
 *  - G
 *  - IWP
 * 
 * \author Johannes Knauf
 */

#ifndef COLLISIONFUNCTOR_NODALSURFACES_HPP
#define COLLISIONFUNCTOR_NODALSURFACES_HPP

#include <Point.hpp>
#include <Disc.hpp>

namespace mcchd
{
  class CF_PSurface {
  private:
    coordinate_type extents;
  public:
    CF_PSurface();
    CF_PSurface(const coordinate_type&);
    ~CF_PSurface();
    bool collides_with(const Disc&) const;
  };

  class CF_DSurface {
  private:
    coordinate_type extents;
  public:
    CF_DSurface();
    CF_DSurface(const coordinate_type&);
    ~CF_DSurface();
    bool collides_with(const Disc&) const;
  };

  class CF_GSurface {
  private:
    coordinate_type extents;
  public:
    CF_GSurface();
    CF_GSurface(const coordinate_type&);
    ~CF_GSurface();
    bool collides_with(const Disc&) const;
  };

  class CF_InnerIWPSurface {
  private:
    coordinate_type extents;
  public:
    CF_InnerIWPSurface();
    CF_InnerIWPSurface(const coordinate_type&);
    ~CF_InnerIWPSurface();
    bool collides_with(const Disc&) const;
  };

  class CF_OuterIWPSurface {
  private:
    coordinate_type extents;
  public:
    CF_OuterIWPSurface();
    CF_OuterIWPSurface(const coordinate_type&);
    ~CF_OuterIWPSurface();
    bool collides_with(const Disc&) const;
  };

}


#include <CollisionFunctor_NodalSurfaces.cpp>

#endif
