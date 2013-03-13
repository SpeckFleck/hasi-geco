// -*- coding: utf-8; -*-
/*!
 * 
 * \file CollisionFunctor_SimpleGeometries.cpp
 * \brief Collision functors modeling Simple Geometries
 * 
 * 
 * 
 * \author Johannes Knauf
 */

#ifdef COLLISIONFUNCTOR_SIMPLEGEOMETRIES_HPP

#include <algorithm>

namespace mcchd
{
  inline CF_InnerSphere::CF_InnerSphere()
  {
  }

  inline CF_InnerSphere::CF_InnerSphere(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);
    // box has to be cubic
    if (extents[0] != extents[1] || extents[1] != extents[2])
      throw bad_extents_exception_sphere();
    
    radius = extents[0]/2.;
  }
  
  inline CF_InnerSphere::~CF_InnerSphere()
  {
  }
  
  inline bool CF_InnerSphere::collides_with(const Disc& some_disc) const
  {
    bool overlaps = center.distance(some_disc.get_center()) > (radius - DEFAULT_DISC_RADIUS);
    return overlaps;
  }


  inline CF_OuterSphere::CF_OuterSphere()
  {
  }

  inline CF_OuterSphere::CF_OuterSphere(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);

    // box has to be cubic
    if (extents[0] != extents[1] || extents[1] != extents[2])
      throw bad_extents_exception_sphere();

    if (extents[0] <= 7.)
      throw bad_extents_exception_sphere();

    radius = (extents[0] - 7.)/2.;
  }
  
  inline CF_OuterSphere::~CF_OuterSphere()
  {
  }
  
  inline bool CF_OuterSphere::collides_with(const Disc& some_disc) const
  {
    bool overlaps = center.distance(some_disc.get_center()) < (radius + DEFAULT_DISC_RADIUS);
    return overlaps;
  }




  inline CF_InnerCylinder::CF_InnerCylinder()
  {
  }

  inline CF_InnerCylinder::CF_InnerCylinder(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., 0.);
    // box has to have quadratic ground plate
    if (extents[0] != extents[1])
      throw bad_extents_exception_cylinder();
    
    radius = extents[0]/2.;
  }
  
  inline CF_InnerCylinder::~CF_InnerCylinder()
  {
  }
  
  inline bool CF_InnerCylinder::collides_with(const Disc& some_disc) const
  {
    Point projected_point = some_disc.get_center();
    /// project coordinate to xy-plane -> set z=0
    projected_point.set_coor(2, 0.);
    bool overlaps = center.distance(projected_point) > (radius - DEFAULT_DISC_RADIUS);
    return overlaps;
  }


  inline CF_OuterCylinder::CF_OuterCylinder()
  {
  }

  inline CF_OuterCylinder::CF_OuterCylinder(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., 0.);

    // box has to have quadratic ground plate
    if (extents[0] != extents[1])
      throw bad_extents_exception_cylinder();
    
    if (extents[0] <= 7.)
      throw bad_extents_exception_cylinder();

    radius = (extents[0] - 7.)/2.;
  }
  
  inline CF_OuterCylinder::~CF_OuterCylinder()
  {
  }
  
  inline bool CF_OuterCylinder::collides_with(const Disc& some_disc) const
  {
    Point projected_point = some_disc.get_center();
    /// project coordinate to xy-plane -> set z=0
    projected_point.set_coor(2, 0.);
    bool overlaps = center.distance(projected_point) < (radius + DEFAULT_DISC_RADIUS);
    return overlaps;
  }

}

#endif
