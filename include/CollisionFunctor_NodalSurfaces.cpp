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
  
  inline bool CF_PSurface::collides_with(const Disc&) const
  {
    return false;
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
  
  inline bool CF_DSurface::collides_with(const Disc&) const
  {
    return false;
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
  
  inline bool CF_GSurface::collides_with(const Disc&) const
  {
    return false;
  }



  inline CF_IWPSurface::CF_IWPSurface()
  {
  }

  inline CF_IWPSurface::CF_IWPSurface(const coordinate_type& new_extents)
  {
    extents = new_extents;
  }
  
  inline CF_IWPSurface::~CF_IWPSurface()
  {
  }
  
  inline bool CF_IWPSurface::collides_with(const Disc&) const
  {
    return false;
  }


}

#endif
