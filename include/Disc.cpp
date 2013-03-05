// -*- coding: utf-8; -*-
/*!
 * \file Disc.cpp
 * \brief Implementation of the disc class.
 * 
 * For usage examples, look at the test cases.
 * 
 * \author Johannes F. Knauf
 */


#ifdef DISC_HPP

namespace mcchd {
  
  inline Disc::Disc()
  {
    center = Point();
    radius = DEFAULT_DISC_RADIUS;
    id = 0;
  }

  inline Disc::Disc(const disc_id_type& new_id)
  {
    center = Point();
    radius = DEFAULT_DISC_RADIUS;
    id = new_id;
  }

  inline Disc::Disc(const Point& at_point, const disc_id_type& new_id)
  {
    center = at_point;
    radius = DEFAULT_DISC_RADIUS;
    id = new_id;
  }

  inline Disc::~Disc()
  {
  }

  inline const Point& Disc::get_center() const
  {
    return center;
  }

  inline void Disc::translate_to(const Point& new_center)
  {
    center = new_center;
  }
  
  inline double Disc::distance(const Disc& other_disc) const
  {
    return this->center.distance(other_disc.center);
  }

  inline bool Disc::is_overlapping(const Disc& other_disc) const
  {
    return distance(other_disc) < (this->radius + other_disc.radius);
  }

  inline bool Disc::operator==(const Disc& other_disc) const
  {
    return (id == other_disc.id);
  }

  inline bool Disc::operator!=(const Disc& other_disc) const
  {
    return ! ((*this) == other_disc);
  }

}

#endif
