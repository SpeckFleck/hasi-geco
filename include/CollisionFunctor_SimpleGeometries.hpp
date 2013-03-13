// -*- coding: utf-8; -*-
/*!
 * 
 * \file CollisionFunctor_SimpleGeometries.hpp
 * \brief Collision functors modeling simple geometries -- header
 * 
 * Implements the surface types:
 *  - inside and outside of a sphere
 *  - inside and outside of a cylinder
 * 
 * \author Johannes Knauf
 */

#ifndef COLLISIONFUNCTOR_SIMPLEGEOMETRIES_HPP
#define COLLISIONFUNCTOR_SIMPLEGEOMETRIES_HPP

#include <exception>

#include <Point.hpp>
#include <Disc.hpp>

namespace mcchd
{

  class bad_extents_exception_sphere : public std::exception
  {
    virtual const char* what() const throw()
    {
      return "Bad extents, box should be cubic for sphere. x, y, z should be larger than or equal to 7. for outer sphere.";
    }
  };

  class bad_extents_exception_cylinder : public std::exception
  {
    virtual const char* what() const throw()
    {
      return "Bad extents, xy ground should be square for cylinder. x, y should be larger than or equal to 7. for outer cylinder.";
    }
  };


  class CF_InnerSphere {
  private:
    coordinate_type extents;
    Point center;
    double radius;
  public:
    CF_InnerSphere();
    CF_InnerSphere(const coordinate_type&);
    ~CF_InnerSphere();
    bool collides_with(const Disc&) const;
  };

  class CF_OuterSphere {
  private:
    coordinate_type extents;
    Point center;
    double radius;
  public:
    CF_OuterSphere();
    CF_OuterSphere(const coordinate_type&);
    ~CF_OuterSphere();
    bool collides_with(const Disc&) const;
  };

  class CF_InnerCylinder {
  private:
    coordinate_type extents;
    Point center;
    double radius;
  public:
    CF_InnerCylinder();
    CF_InnerCylinder(const coordinate_type&);
    ~CF_InnerCylinder();
    bool collides_with(const Disc&) const;
  };

  class CF_OuterCylinder {
  private:
    coordinate_type extents;
    Point center;
    double radius;
  public:
    CF_OuterCylinder();
    CF_OuterCylinder(const coordinate_type&);
    ~CF_OuterCylinder();
    bool collides_with(const Disc&) const;
  };



}


#include <CollisionFunctor_SimpleGeometries.cpp>

#endif
