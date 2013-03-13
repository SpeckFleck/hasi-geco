// -*- coding: utf-8; -*-
/*!
 * 
 * \file CollisionFunctor_NodalSurfaces.cpp
 * \brief Collision functors modeling nodal surfaces
 * 
 * 
 * 
 * \author Johannes Knauf
 */

#ifdef COLLISIONFUNCTOR_NODALSURFACES_HPP

#include <cmath>


namespace mcchd
{
  inline CF_PSurface::CF_PSurface()
  {
  }

  inline CF_PSurface::CF_PSurface(const coordinate_type& new_extents)
  {
    extents = new_extents;
  }
  
  inline CF_PSurface::~CF_PSurface()
  {
  }
  
  inline bool CF_PSurface::collides_with(const Disc& some_disc) const
  {
    const Point disc_center = some_disc.get_center();
    const double x = disc_center.get_coor(0);
    const double y = disc_center.get_coor(1);
    const double z = disc_center.get_coor(2);
    bool overlaps = std::cos(2.*M_PI/extents[0] * x) + std::cos(2.*M_PI/extents[1] * y) + std::cos(2.*M_PI/extents[2] * z) < 0;
    return overlaps;
  }


  inline CF_DSurface::CF_DSurface()
  {
  }

  inline CF_DSurface::CF_DSurface(const coordinate_type& new_extents)
  {
    extents = new_extents;
  }
  
  inline CF_DSurface::~CF_DSurface()
  {
  }
  
  inline bool CF_DSurface::collides_with(const Disc& some_disc) const
  {
    const Point disc_center = some_disc.get_center();
    const double x = disc_center.get_coor(0);
    const double y = disc_center.get_coor(1);
    const double z = disc_center.get_coor(2);
    bool overlaps = (std::sin(2.*M_PI/extents[0] * x) * std::sin(2.*M_PI/extents[1] * y) * std::sin(2.*M_PI/extents[2] * z) +
		     std::sin(2.*M_PI/extents[0] * x) * std::cos(2.*M_PI/extents[1] * y) * std::cos(2.*M_PI/extents[2] * z) +
		     std::cos(2.*M_PI/extents[0] * x) * std::sin(2.*M_PI/extents[1] * y) * std::cos(2.*M_PI/extents[2] * z) +
		     std::cos(2.*M_PI/extents[0] * x) * std::cos(2.*M_PI/extents[1] * y) * std::sin(2.*M_PI/extents[2] * z) ) < 0;
    return overlaps;
  }



  inline CF_GSurface::CF_GSurface()
  {
  }

  inline CF_GSurface::CF_GSurface(const coordinate_type& new_extents)
  {
    extents = new_extents;
  }
  
  inline CF_GSurface::~CF_GSurface()
  {
  }
  
  inline bool CF_GSurface::collides_with(const Disc& some_disc) const
  {
  const Point disc_center = some_disc.get_center();
    const double x = disc_center.get_coor(0);
    const double y = disc_center.get_coor(1);
    const double z = disc_center.get_coor(2);
    bool overlaps = (std::cos(2.*M_PI/extents[0] * x) * std::sin(2.*M_PI/extents[1] * y) +
		     std::cos(2.*M_PI/extents[1] * y) * std::sin(2.*M_PI/extents[2] * z) +
		     std::cos(2.*M_PI/extents[2] * z) * std::sin(2.*M_PI/extents[0] * x) ) < 0;
    return overlaps;
  }



  inline CF_InnerIWPSurface::CF_InnerIWPSurface()
  {
  }

  inline CF_InnerIWPSurface::CF_InnerIWPSurface(const coordinate_type& new_extents)
  {
    extents = new_extents;
  }
  
  inline CF_InnerIWPSurface::~CF_InnerIWPSurface()
  {
  }
  
  inline bool CF_InnerIWPSurface::collides_with(const Disc& some_disc) const
  {
    const Point disc_center = some_disc.get_center();
    const double x = disc_center.get_coor(0);
    const double y = disc_center.get_coor(1);
    const double z = disc_center.get_coor(2);
    bool overlaps = 2*(std::cos(2.*M_PI/extents[0] * x) * std::cos(2.*M_PI/extents[1] * y) +
		       std::cos(2.*M_PI/extents[1] * y) * std::cos(2.*M_PI/extents[2] * z) +
		       std::cos(2.*M_PI/extents[2] * z) * std::cos(2.*M_PI/extents[0] * x) )
      - (std::cos(4.*M_PI/extents[0] * x) + std::cos(4.*M_PI/extents[1] * y) + std::cos(4.*M_PI/extents[2] * z)) < 0;
    return overlaps;
  }

  inline CF_OuterIWPSurface::CF_OuterIWPSurface()
  {
  }

  inline CF_OuterIWPSurface::CF_OuterIWPSurface(const coordinate_type& new_extents)
  {
    extents = new_extents;
  }
  
  inline CF_OuterIWPSurface::~CF_OuterIWPSurface()
  {
  }
  
  inline bool CF_OuterIWPSurface::collides_with(const Disc& some_disc) const
  {
    const Point disc_center = some_disc.get_center();
    const double x = disc_center.get_coor(0);
    const double y = disc_center.get_coor(1);
    const double z = disc_center.get_coor(2);
    bool overlaps = 2*(std::cos(2.*M_PI/extents[0] * x) * std::cos(2.*M_PI/extents[1] * y) +
		       std::cos(2.*M_PI/extents[1] * y) * std::cos(2.*M_PI/extents[2] * z) +
		       std::cos(2.*M_PI/extents[2] * z) * std::cos(2.*M_PI/extents[0] * x) )
      - (std::cos(4.*M_PI/extents[0] * x) + std::cos(4.*M_PI/extents[1] * y) + std::cos(4.*M_PI/extents[2] * z)) > 0;
    return overlaps;
  }


}

#endif
