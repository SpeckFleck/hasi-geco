// -*- coding: utf-8; -*-
/*!
 * 
 * \file CollisionFunctor_SingularDefects.cpp
 * \brief Prototype example of a CollisionFunctor
 * 
 * 
 * 
 * \author Johannes Knauf
 */

#ifdef COLLISIONFUNCTOR_SINGULARDEFECTS_HPP

namespace mcchd {

  inline CF_Bulk::CF_Bulk()
  {
  }

  inline CF_Bulk::CF_Bulk(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);
  }
  
  inline CF_Bulk::~CF_Bulk()
  {
  }
  
  inline bool CF_Bulk::collides_with(const Disc&) const
  {
    return false;
  }


  inline CF_PointDefect::CF_PointDefect()
  {
  }

  inline CF_PointDefect::CF_PointDefect(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., extents[2]/2.);
  }
  
  inline CF_PointDefect::~CF_PointDefect()
  {
  }
  
  inline bool CF_PointDefect::collides_with(const Disc& some_disc) const
  {
    /// point is placed in the center
    return (center.distance(some_disc.get_center())) < DEFAULT_DISC_RADIUS;
  }



  inline CF_LineDefect::CF_LineDefect()
  {
  }

  inline CF_LineDefect::CF_LineDefect(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2., extents[1]/2., 0.);
  }
  
  inline CF_LineDefect::~CF_LineDefect()
  {
  }
  
  inline bool CF_LineDefect::collides_with(const Disc& some_disc) const
  {
    Point projected_point = some_disc.get_center();
    /// project coordinate to xy-plane -> set z=0
    projected_point.set_coor(2, 0.);
    return (center.distance(projected_point)) < DEFAULT_DISC_RADIUS;
  }



  inline CF_PlaneDefect::CF_PlaneDefect()
  {
  }

  inline CF_PlaneDefect::CF_PlaneDefect(const coordinate_type& new_extents)
  {
    extents = new_extents;
    center = Point(extents[0]/2.,  0., 0.);
  }
  
  inline CF_PlaneDefect::~CF_PlaneDefect()
  {
  }
  
  inline bool CF_PlaneDefect::collides_with(const Disc& some_disc) const
  {
    Point projected_point = some_disc.get_center();
    /// project coordinate to x line, plane is at x = 1/2 * x_max
    projected_point.set_coor(1, 0.);
    projected_point.set_coor(2, 0.);
    return (center.distance(projected_point)) < DEFAULT_DISC_RADIUS;
  }





}

#endif

