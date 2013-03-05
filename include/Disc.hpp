// -*- coding: utf-8; -*-
/*!
 * \file Disc.hpp
 * \brief Class for discs
 * 
 * It contains a center point, a radius and a unique ID.
 * 
 * \author Johannes F. Knauf
 */

#ifndef DISC_HPP
#define DISC_HPP

#define DEFAULT_DISC_RADIUS 0.5

#include <cstdint>
#include <Point.hpp>

namespace mcchd {

  typedef uint32_t disc_id_type;

  class Disc {
  private:
    Point center;
    double radius;
    disc_id_type id;
  public:
    Disc();
    Disc(const disc_id_type&);
    Disc(const Point&, const disc_id_type&);
    ~Disc();
    const Point& get_center() const;
    void translate_to(const Point&);
    double distance(const Disc&) const;
    bool is_overlapping(const Disc&) const;
    bool operator==(const Disc&) const;
    bool operator!=(const Disc&) const;
  };

}

#include <Disc.cpp>

#endif
