#include "geometric_utils.h"

/**
 * @brief geometricUtils::slope returns the slope of the segment.
 * @param segment is the segment whose slope to calculate.
 * @return the slope of the segment.
 */
double geometricUtils::slope(const cg3::Segment2d& segment) {
    return (segment.p1().y() - segment.p2().y()) / (segment.p1().x() - segment.p2().x());
}
