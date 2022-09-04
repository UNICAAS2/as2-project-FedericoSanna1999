#include "geometric_utils.h"

/**
 * @brief geometricUtils::slope returns the slope of the segment.
 * @param segment is the segment whose slope to calculate.
 * @return the slope of the segment.
 */
double geometricUtils::slope(const cg3::Segment2d& segment) {
    return (segment.p1().y() - segment.p2().y()) / (segment.p1().x() - segment.p2().x());
}

/**
 * @brief geometricUtils::intersection returns the point which has the x coordinate and lies on the segment.
 * @param segment is the segment where the point to calculate lies on.
 * @param x is the x coordinate which the point has.
 * @return the point which has the x coordinate and lies on the segment.
 */
const cg3::Point2d geometricUtils::intersection(const cg3::Segment2d& segment, const double& x) {
    const double& m = slope(segment);
    const double q = segment.p1().y() - m * segment.p1().x();
    return cg3::Point2d(x, m * x + q);
}
