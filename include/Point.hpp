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

#include <random_boost_mt19937.hpp>
#include <array>

namespace mcchd {

  typedef std::array<double, 3> coordinate_type;

  template <class RandomNumberGenerator = Boost_MT19937>
  class Point_3d {
  private:
    coordinate_type coors;
  public:
    Point_3d();
    Point_3d(RandomNumberGenerator*, const coordinate_type&); // random point in container
    Point_3d(const double&, const double&, const double&);
    Point_3d(const coordinate_type&);
    ~Point_3d();
    double get_coor(const uint8_t&) const;
    void set_coor(const uint8_t&, const double&);
    double abs() const;
    double distance(const Point_3d<RandomNumberGenerator>&) const;
    Point_3d<RandomNumberGenerator> operator-(const Point_3d<RandomNumberGenerator>&) const;
    bool operator==(const Point_3d<RandomNumberGenerator>&) const;
    bool operator!=(const Point_3d<RandomNumberGenerator>&) const;
  };

  typedef Point_3d<Boost_MT19937> Point;
}


#include <Point.cpp>

#endif
