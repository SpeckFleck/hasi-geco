/*!
 * \file Point.cpp
 * \brief Implementation of the 3d point class.
 * 
 * For usage examples, look at the test cases.
 * 
 * \author Johannes F. Knauf
 */


#ifdef POINT_HPP

#include <cmath>
#include <algorithm>

namespace mcchd {

  inline Point_3d::Point_3d()
  {
    coors[0] = 0.;
    coors[1] = 0.;
    coors[2] = 0.;
  }

  inline Point_3d::Point_3d(const double& x, const double& y, const double& z)
  {
    coors[0] = x;
    coors[1] = y;
    coors[2] = z;
  }

  template <class RandomNumberGenerator>
  inline Point_3d::Point_3d(RandomNumberGenerator* rng, const coordinate_type& extents)
  {
    coors[0] = rng->random_double() * extents[0];
    coors[1] = rng->random_double() * extents[1];
    coors[2] = rng->random_double() * extents[2];
  }

  template <class RandomNumberGenerator>
  inline Point_3d::Point_3d(RandomNumberGenerator* rng, const double& max_displacement)
  {
    const double phi = rng->random_double() * 2. * M_PI;
    const double theta = asin(rng->random_double() * 2. - 1.);
    const double R = pow(rng->random_double() * max_displacement * max_displacement * max_displacement, 1./3.);
    coors[0] = R * cos(theta) * cos(phi);
    coors[1] = R * cos(theta) * sin(phi);
    coors[2] = R * sin(theta);
  }

  inline Point_3d::Point_3d(const coordinate_type& new_coors)
  {
    coors = new_coors;
  }

  inline Point_3d::~Point_3d()
  {
  }

  inline double Point_3d::get_coor(const uint8_t& idx) const
  {
    return coors[idx];
  }
  
  inline void Point_3d::set_coor(const uint8_t& idx, const double& new_coor)
  {
    coors[idx] = new_coor;
  }

  inline void Point_3d::rebase_periodic(const coordinate_type& extents)
  {
    while (coors[0] < 0)
      coors[0] += extents[0];
    while (coors[1] < 0)
      coors[1] += extents[1];
    while (coors[2] < 0)
      coors[2] += extents[2];

    coors[0] = fmod(coors[0], extents[0]);
    coors[1] = fmod(coors[1], extents[1]);
    coors[2] = fmod(coors[2], extents[2]);
  }

  inline double Point_3d::absolute() const
  {
    return sqrt(coors[0]*coors[0] + coors[1]*coors[1] + coors[2]*coors[2]);
  }
  
  inline double Point_3d::distance(const Point_3d& other_point) const
  {
    return (other_point - (*this)).absolute();
  }

  inline double Point_3d::distance(const Point_3d& other_point, const coordinate_type& extents) const
  {
    const double d_x = fabs(other_point.coors[0] - coors[0]);
    const double d_x_alt = extents[0] - d_x;
    const double d_x_pbc = std::min(d_x, d_x_alt);

    const double d_y = fabs(other_point.coors[1] - coors[1]);
    const double d_y_alt = extents[1] - d_y;
    const double d_y_pbc = std::min(d_y, d_y_alt);

    const double d_z = fabs(other_point.coors[2] - coors[2]);
    const double d_z_alt = extents[2] - d_z;
    const double d_z_pbc = std::min(d_z, d_z_alt);

    return sqrt(d_x_pbc*d_x_pbc + d_y_pbc*d_y_pbc + d_z_pbc*d_z_pbc);
  }
  
  inline Point_3d Point_3d::operator- () const
  {
    return Point_3d(- coors[0], - coors[1], - coors[2]);
  }

  inline Point_3d Point_3d::operator- (const Point_3d& other_point) const
  {
    return Point_3d(coors[0] - other_point.coors[0], coors[1] - other_point.coors[1], coors[2] - other_point.coors[2]);
  }

  inline Point_3d Point_3d::operator+ (const Point_3d& other_point) const
  {
    return Point_3d(coors[0] + other_point.coors[0], coors[1] + other_point.coors[1], coors[2] + other_point.coors[2]);
  }

  inline bool Point_3d::operator== (const Point_3d& other_point) const
  {
    return coors[0] == other_point.coors[0] && coors[1] == other_point.coors[1] && coors[2] == other_point.coors[2];
  }

  inline bool Point_3d::operator!= (const Point_3d& other_point) const
  {
    return !((*this) == other_point);
  }

  std::ostream& operator<<(std::ostream& out_stream, const Point_3d& to_be_printed)
  {
    out_stream << "(" << to_be_printed.coors[0];
    out_stream << ", " << to_be_printed.coors[1];
    out_stream << ", " << to_be_printed.coors[2] << ")";
    return out_stream;
  }


} // end namespace mcchd


#endif

