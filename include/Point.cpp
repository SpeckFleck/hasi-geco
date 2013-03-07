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

namespace mcchd {

  template <class RandomNumberGenerator>
  Point_3d<RandomNumberGenerator>::Point_3d()
  {
    coors[0] = 0.;
    coors[1] = 0.;
    coors[2] = 0.;
  }

  template <class RandomNumberGenerator>
  Point_3d<RandomNumberGenerator>::Point_3d(const double& x, const double& y, const double& z)
  {
    coors[0] = x;
    coors[1] = y;
    coors[2] = z;
  }

  template <class RandomNumberGenerator>
  Point_3d<RandomNumberGenerator>::Point_3d(RandomNumberGenerator* rng, const coordinate_type& extents)
  {
    coors[0] = rng->random_double() * extents[0];
    coors[1] = rng->random_double() * extents[1];
    coors[2] = rng->random_double() * extents[2];
  }

  template <class RandomNumberGenerator>
  Point_3d<RandomNumberGenerator>::Point_3d(const coordinate_type& new_coors)
  {
    coors = new_coors;
  }

  template <class RandomNumberGenerator>
  Point_3d<RandomNumberGenerator>::~Point_3d()
  {
  }

  template <class RandomNumberGenerator>
  double Point_3d<RandomNumberGenerator>::get_coor(const uint8_t& idx) const
  {
    return coors[idx];
  }
  
  template <class RandomNumberGenerator>
  void Point_3d<RandomNumberGenerator>::set_coor(const uint8_t& idx, const double& new_coor)
  {
    coors[idx] = new_coor;
  }

  template <class RandomNumberGenerator>
  double Point_3d<RandomNumberGenerator>::absolute() const
  {
    return sqrt(coors[0]*coors[0] + coors[1]*coors[1] + coors[2]*coors[2]);
  }
  
  template <class RandomNumberGenerator>
  double Point_3d<RandomNumberGenerator>::distance(const Point_3d<RandomNumberGenerator>& other_point) const
  {
    return (other_point - (*this)).absolute();
  }

  template <class RandomNumberGenerator>
  double Point_3d<RandomNumberGenerator>::distance(const Point_3d<RandomNumberGenerator>& other_point, const coordinate_type& extents) const
  {
    const double x_center = extents[0]/2.;
    const double d_x = abs(other_point.coors[0] - coors[0]);
    const double d_x_pbc = d_x < x_center ? d_x : x_center - d_x;

    const double y_center = extents[1]/2.;
    const double d_y = abs(other_point.coors[1] - coors[1]);
    const double d_y_pbc = d_y < y_center ? d_y : y_center - d_y;

    const double z_center = extents[2]/2.;
    const double d_z = abs(other_point.coors[2] - coors[2]);
    const double d_z_pbc = d_z < z_center ? d_z : z_center - d_z;

    return sqrt(d_x_pbc*d_x_pbc + d_y_pbc*d_y_pbc + d_z_pbc*d_z_pbc);
  }
  
  template <class RandomNumberGenerator>
  Point_3d<RandomNumberGenerator> Point_3d<RandomNumberGenerator>::operator- (const Point_3d<RandomNumberGenerator>& other_point) const
  {
    return Point_3d<RandomNumberGenerator>(coors[0] - other_point.coors[0], coors[1] - other_point.coors[1], coors[2] - other_point.coors[2]);
  }

  template <class RandomNumberGenerator>
  bool Point_3d<RandomNumberGenerator>::operator== (const Point_3d<RandomNumberGenerator>& other_point) const
  {
    return coors[0] == other_point.coors[0] && coors[1] == other_point.coors[1] && coors[2] == other_point.coors[2];
  }

  template <class RandomNumberGenerator>
  bool Point_3d<RandomNumberGenerator>::operator!= (const Point_3d<RandomNumberGenerator>& other_point) const
  {
    return !((*this) == other_point);
  }
} // end namespace mcchd

#endif

