#ifndef GEOMETRIC_UTILS_H
#define GEOMETRIC_UTILS_H

#include <cg3/geometry/segment2.h>
#include <cg3/geometry/point2.h>

namespace geometricUtils {
    double slope(const cg3::Segment2d& segment);
    const cg3::Point2d intersection(const cg3::Segment2d& segment, const double& x);
}

#endif // GEOMETRIC_UTILS_H
