// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//

// release       :
// release_date  :
//
// file          : include/CGAL/predicates/kernel_ftC2.h
// source        : include/CGAL/predicates/kernel_ftC2.h
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Herve Bronnimann (Herve.Bronnimann@sophia.inria.fr)
//                 Sylvain Pion     (Sylvain.Pion@sophia.inria.fr)
//
// coordinator   : INRIA Sophia-Antipolis (Herve.Bronnimann@sophia.inria.fr)
//
// ============================================================================


#ifndef CGAL_PREDICATES_KERNEL_FTC2_H
#define CGAL_PREDICATES_KERNEL_FTC2_H

#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif // CGAL_NUMBER_UTILS_H
#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H
#ifndef CGAL_CONSTRUCTIONS_KERNEL_FTC2_H
#include <CGAL/constructions/kernel_ftC2.h>
#endif // CGAL_CONSTRUCTIONS_KERNEL_FTC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_xC2(const FT &px,
            const FT &l1a, const FT &l1b, const FT &l1c,
            const FT &l2a, const FT &l2b, const FT &l2c)
{
  // The abscissa of the intersection point is num/den.
  FT num = det2x2_by_formula( l1b, l1c, l2b, l2c);
  FT den = det2x2_by_formula( l1a, l1b, l2a, l2b);
  Sign s = CGAL::sign(den);
  CGAL_kernel_assertion( s != ZERO );
  return Comparison_result( s * CGAL::compare( px * den, num) );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
            const FT &l2a, const FT &l2b, const FT &l2c,
            const FT &h1a, const FT &h1b, const FT &h1c,
            const FT &h2a, const FT &h2b, const FT &h2c)
{
  FT numl = det2x2_by_formula( l1b, l1c, l2b, l2c);
  FT denl = det2x2_by_formula( l1a, l1b, l2a, l2b);
  FT numh = det2x2_by_formula( h1b, h1c, h2b, h2c);
  FT denh = det2x2_by_formula( h1a, h1b, h2a, h2b);
  Sign s = Sign (CGAL::sign(denl) * CGAL::sign(denh));
  CGAL_kernel_assertion( s != ZERO );
  return Comparison_result( s * sign_of_determinant2x2(denh, numh, denl, numl));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_xC2(const FT &px, const FT &py,
                 const FT &la, const FT &lb, const FT &lc)
{
  Sign s = CGAL::sign(lb);
  CGAL_kernel_assertion( s != ZERO );
  return Comparison_result (s * CGAL::sign(la*px + lb*py + lc));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_xC2(const FT &px,
                 const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c)
{
  Sign s = Sign (CGAL::sign(l1b) * CGAL::sign(l2b));
  CGAL_kernel_assertion( s != ZERO );
  return Comparison_result ( s * sign_of_determinant2x2(l2a*px+l2c, l2b,
                                                        l1a*px+l1c, l1b));
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c,
                 const FT &ha,  const FT &hb,  const FT &hc)
{
  Sign s = Sign (sign_of_determinant2x2(l1a, l1b, l2a, l2b) * CGAL::sign(hb));
  CGAL_kernel_assertion( s != ZERO );
  return Comparison_result( s * sign_of_determinant3x3(l1a, l1b, l1c,
                                                       l2a, l2b, l2c,
                                                       ha,  hb,  hc));
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Comparison_result
compare_y_at_xC2(const FT &l1a, const FT &l1b, const FT &l1c,
                 const FT &l2a, const FT &l2b, const FT &l2c,
                 const FT &h1a, const FT &h1b, const FT &h1c,
                 const FT &h2a, const FT &h2b, const FT &h2c)
{
  // The abscissa of the intersection point is num/den.
  FT num = det2x2_by_formula( l1b, l1c, l2b, l2c);
  FT den = det2x2_by_formula( l1a, l1b, l2a, l2b);
  Sign s = Sign (CGAL::sign(h1b) * CGAL::sign(h2b) * CGAL::sign(den));
  CGAL_kernel_assertion( s != ZERO );
  return Comparison_result ( s * sign_of_determinant2x2(h2a*num+h2c*den, h2b,
                                                        h1a*num+h1c*den, h1b));
}

template < class FT >
inline
Comparison_result
compare_deltax_deltayC2(const FT &px, const FT &qx,
                        const FT &ry, const FT &sy)
{
  return CGAL::compare(abs(px-qx), abs(ry-sy));
}

template < class FT >
inline
Comparison_result
compare_lexicographically_xyC2(const FT &px, const FT &py,
                               const FT &qx, const FT &qy)
{
  Comparison_result c = CGAL::compare(px,qx);
  return (c != EQUAL) ? c : CGAL::compare(py,qy);
}

template < class FT >
inline
Orientation
orientationC2(const FT &px, const FT &py,
              const FT &qx, const FT &qy,
              const FT &rx, const FT &ry)
{
  return Orientation (sign_of_determinant2x2(px-rx, py-ry,
                                             qx-rx, qy-ry));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_ordered_along_lineC2(const FT &px, const FT &py,
                                   const FT &qx, const FT &qy,
                                   const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  if (px < qx) return !(rx < qx);
  if (qx < px) return !(qx < rx);
  if (py < qy) return !(ry < qy);
  if (qy < py) return !(qy < ry);
  return true; // p==q
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_strictly_ordered_along_lineC2(const FT &px, const FT &py,
                                            const FT &qx, const FT &qy,
                                            const FT &rx, const FT &ry)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  if (px < qx) return (qx < rx);
  if (qx < px) return (rx < qx);
  if (py < qy) return (qy < ry);
  if (qy < py) return (ry < qy);
  return false;
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Oriented_side
side_of_oriented_circleC2(const FT &px, const FT &py,
                          const FT &qx, const FT &qy,
                          const FT &rx, const FT &ry,
                          const FT &tx, const FT &ty)
{
  // Oriented_side(
  //  sign_of_determinant4x4(px, py, px*px + py*py, 1,
  //                         qx, qy, qx*qx + qy*qy, 1,
  //                         rx, ry, rx*rx + ry*ry, 1,
  //                         tx, ty, tx*tx + ty*ty, 1));
  // We first translate so that t is the new origin.
  FT ptx = px-tx;
  FT pty = py-ty;
  FT qtx = qx-tx;
  FT qty = qy-ty;
  FT rtx = rx-tx;
  FT rty = ry-ty;
// The usual 3x3 formula can be simplified a little bit to a 2x2.
//           sign_of_determinant3x3(ptx, pty, square(ptx) + square(pty),
//                                  qtx, qty, square(qtx) + square(qty),
//                                  rtx, rty, square(rtx) + square(rty)));
  return Oriented_side( sign_of_determinant2x2(
                             ptx*qty - pty*qtx, qtx*(qx-px) + qty*(qy-py),
                             ptx*rty - pty*rtx, rtx*(rx-px) + rty*(ry-py)));
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
Bounded_side
side_of_bounded_circleC2(const FT &px, const FT &py,
                         const FT &qx, const FT &qy,
                         const FT &rx, const FT &ry,
                         const FT &tx, const FT &ty)
{
  // Note: if the code of these is inlined, and if they are implemented
  // in a good way, some CSE can be done by the compiler.
  return Bounded_side( side_of_oriented_circleC2(px,py,qx,qy,rx,ry,tx,ty)
                                 * orientationC2(px,py,qx,qy,rx,ry) );
}

template < class FT >
inline
Comparison_result
cmp_dist_to_pointC2(const FT &px, const FT &py,
                    const FT &qx, const FT &qy,
                    const FT &rx, const FT &ry)
{
  return CGAL::compare(squared_distanceC2(px,py,qx,qy),
                       squared_distanceC2(px,py,rx,ry));
}

template < class FT >
inline
bool
has_larger_dist_to_pointC2(const FT &px, const FT &py,
                           const FT &qx, const FT &qy,
                           const FT &rx, const FT &ry)
{
  return squared_distanceC2(px,py,rx,ry)
       < squared_distanceC2(px,py,qx,qy);
}

template < class FT >
inline
bool
has_smaller_dist_to_pointC2(const FT &px, const FT &py,
                            const FT &qx, const FT &qy,
                            const FT &rx, const FT &ry)
{
  return squared_distanceC2(px,py,qx,qy)
       < squared_distanceC2(px,py,rx,ry);
}

template < class FT >
inline
Comparison_result
cmp_signed_dist_to_directionC2(const FT &la, const FT &lb,
                               const FT &px, const FT &py,
                               const FT &qx, const FT &qy)
{
  return CGAL::compare(scaled_distance_to_directionC2(la,lb,px,py),
                       scaled_distance_to_directionC2(la,lb,qx,qy));
}

template < class FT >
inline
bool
has_larger_signed_dist_to_directionC2(const FT &la, const FT &lb,
                                      const FT &px, const FT &py,
                                      const FT &qx, const FT &qy)
{
  return scaled_distance_to_directionC2(la,lb,qx,qy)
       < scaled_distance_to_directionC2(la,lb,px,py);
}

template < class FT >
inline
bool
has_smaller_signed_dist_to_directionC2(const FT &la, const FT &lb,
                                       const FT &px, const FT &py,
                                       const FT &qx, const FT &qy)
{
  return scaled_distance_to_directionC2(la,lb,px,py)
       < scaled_distance_to_directionC2(la,lb,qx,qy);
}
template <class FT>
inline
Comparison_result
cmp_signed_dist_to_lineC2(const FT &px, const FT &py,
                          const FT &qx, const FT &qy,
                          const FT &rx, const FT &ry,
                          const FT &sx, const FT &sy)
{
  return CGAL::compare(scaled_distance_to_lineC2(px,py,qx,qy,rx,ry),
                       scaled_distance_to_lineC2(px,py,qx,qy,sx,sy));
}

template <class FT>
inline
bool
has_larger_signed_dist_to_lineC2(const FT &px, const FT &py,
                                 const FT &qx, const FT &qy,
                                 const FT &rx, const FT &ry,
                                 const FT &sx, const FT &sy)
{
  return scaled_distance_to_lineC2(px,py,qx,qy,sx,sy)
       < scaled_distance_to_lineC2(px,py,qx,qy,rx,ry);
}

template <class FT>
inline
bool
has_smaller_signed_dist_to_lineC2(const FT &px, const FT &py,
                                  const FT &qx, const FT &qy,
                                  const FT &rx, const FT &ry,
                                  const FT &sx, const FT &sy)
{
  return scaled_distance_to_lineC2(px,py,qx,qy,rx,ry)
       < scaled_distance_to_lineC2(px,py,qx,qy,sx,sy);
}


CGAL_END_NAMESPACE

#ifdef CGAL_ARITHMETIC_FILTER_H
#ifndef CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
#include <CGAL/Arithmetic_filter/predicates/kernel_ftC2.h>
#endif // CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC2_H
#endif

#endif  // CGAL_PREDICATES_KERNEL_FTC2_H
