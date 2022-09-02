#include "algorithms.h"

#include <cg3/geometry/utils2.h>

/**
 * @brief algorithms::query returns the trapezoid index where the query point is in, using the directed acyclig graph and the trapezoidal map.
 * @param trapezoidalMap contains all points, segments, and trapezoids.
 * @param directedAcyclicGraph contains all point, segment, and trapezoid nodes.
 * @param queryPoint is the point used to find the trapezoid which contains it.
 * @return the trapezoid index where the query point is in.
 */
size_t algorithms::query(const TrapezoidalMap& trapezoidalMap, const DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Point2d& queryPoint) {
    const std::vector<cg3::Point2d>& points = trapezoidalMap.getPoints();
    const std::vector<Node>& nodes = directedAcyclicGraph.getNodes();
    size_t id = 0;

    while (nodes[id].getType() != Node::TRAPEZOID)
        if (nodes[id].getType() == Node::POINT)
            if (points[nodes[id].getObject()].x() > queryPoint.x())
                id = nodes[id].getLeftChild();
            else
                id = nodes[id].getRightChild();
        else
            if (cg3::isPointAtLeft(trapezoidalMap.getSegment(nodes[id].getObject()), queryPoint))
                id = nodes[id].getLeftChild();
            else
                id = nodes[id].getRightChild();

    return nodes[id].getObject();
}
