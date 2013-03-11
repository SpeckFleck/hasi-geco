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

namespace mcchd
{
  inline CF_InnerSphere::CF_InnerSphere()
  {
  }

  inline CF_InnerSphere::CF_InnerSphere(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);
  }
  
  inline CF_InnerSphere::~CF_InnerSphere()
  {
  }
  
  inline bool CF_InnerSphere::collides_with(const Disc&) const
  {
    return false;
  }


  inline CF_OuterSphere::CF_OuterSphere()
  {
  }

  inline CF_OuterSphere::CF_OuterSphere(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);
  }
  
  inline CF_OuterSphere::~CF_OuterSphere()
  {
  }
  
  inline bool CF_OuterSphere::collides_with(const Disc&) const
  {
    return false;
  }




  inline CF_InnerCylinder::CF_InnerCylinder()
  {
  }

  inline CF_InnerCylinder::CF_InnerCylinder(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);
  }
  
  inline CF_InnerCylinder::~CF_InnerCylinder()
  {
  }
  
  inline bool CF_InnerCylinder::collides_with(const Disc&) const
  {
    return false;
  }


  inline CF_OuterCylinder::CF_OuterCylinder()
  {
  }

  inline CF_OuterCylinder::CF_OuterCylinder(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);
  }
  
  inline CF_OuterCylinder::~CF_OuterCylinder()
  {
  }
  
  inline bool CF_OuterCylinder::collides_with(const Disc&) const
  {
    return false;
  }

}

#endif
