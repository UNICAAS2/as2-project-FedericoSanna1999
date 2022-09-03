#include "algorithms.h"

#include <cg3/geometry/utils2.h>
#include "utils/geometric_utils.h"

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

/**
 * @brief algorithms::find returns the trapezoid index where the left point of the segment is in, using the directed acyclic graph and the trapezoidal map.
 * @param trapezoidalMap contains all points, segments, and trapezoids.
 * @param directedAcyclicGraph contains all point, segment, and trapezoid nodes.
 * @param segment is the segment used to find the trapezoid which contains its left point.
 * @return the trapezoid index where the left point of the segment is in.
 */
size_t algorithms::find(const TrapezoidalMap& trapezoidalMap, const DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Segment2d& segment) {
    const std::vector<cg3::Point2d>& points = trapezoidalMap.getPoints();
    const std::vector<Node>& nodes = directedAcyclicGraph.getNodes();
    const cg3::Point2d& queryPoint = segment.p1();
    const double& slope = geometricUtils::slope(segment);
    size_t id = 0;

    while (nodes[id].getType() != Node::TRAPEZOID)
        if (nodes[id].getType() == Node::POINT)
            if (points[nodes[id].getObject()].x() > queryPoint.x())
                id = nodes[id].getLeftChild();
            else
                id = nodes[id].getRightChild();
        else
            if (trapezoidalMap.getSegment(nodes[id].getObject()).p1() == queryPoint)
                if (slope > geometricUtils::slope(trapezoidalMap.getSegment(nodes[id].getObject())))
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
