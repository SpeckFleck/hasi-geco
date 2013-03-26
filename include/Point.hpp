/*!
 * \file Point.hpp
 * \brief Class for 3d point arithmetic.
 * 
 * It contains coordinates and provides operations thereupon.
 * 
 * \author Johannes F. Knauf
 */

#ifndef POINT_HPP
#define POINT_HPP

#include <boost/array.hpp>

namespace mcchd {

  typedef boost::array<double, 3> coordinate_type;

  class Point_3d {
  private:
    coordinate_type coors;
  public:
    Point_3d();
    template <class RandomNumberGenerator> Point_3d(RandomNumberGenerator*, const coordinate_type&); // random point in container
    Point_3d(const double&, const double&, const double&);
    Point_3d(const coordinate_type&);
    ~Point_3d();
    double get_coor(const uint8_t&) const;
    void set_coor(const uint8_t&, const double&);
    double absolute() const;
    double distance(const Point_3d&) const;
    double distance(const Point_3d&, const coordinate_type&) const;
    Point_3d operator-(const Point_3d&) const;
    bool operator==(const Point_3d&) const;
    bool operator!=(const Point_3d&) const;
  };

  typedef Point_3d Point;
}


#include <Point.cpp>

#endif
