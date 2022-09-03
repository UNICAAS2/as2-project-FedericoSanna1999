#include "algorithms.h"

#include <cg3/geometry/utils2.h>
#include "utils/geometric_utils.h"

/**
 * @brief algorithms::add allows updating the data structures with the new segment.
 * @param trapezoidalMap contains all points, segments, and trapezoids.
 * @param directedAcyclicGraph contains all point, segment, and trapezoid nodes.
 * @param segment is the segment added to the data structures.
 */
void algorithms::add(TrapezoidalMap& trapezoidalMap, DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Segment2d& segment) {
    std::vector<size_t> intersectedTrapezoids;

    const size_t& id = trapezoidalMap.addSegment(segment);

    followSegment(trapezoidalMap, directedAcyclicGraph, trapezoidalMap.getSegment(id), intersectedTrapezoids);

    // TODO: update data structures
}

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

/**
 * @brief algorithms::followSegment allows to find the trapezoids which are intersected by the segment.
 * @param trapezoidalMap contains all points, segments, and trapezoids.
 * @param directedAcyclicGraph contains all point, segment, and trapezoid nodes.
 * @param segment is the segment used to find the trapezoids which are intersected by it.
 * @param intersectedTrapezoids is the vector which contains the trapezoids which are intersected by the segment.
 */
void algorithms::followSegment(const TrapezoidalMap& trapezoidalMap, const DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Segment2d& segment, std::vector<size_t>& intersectedTrapezoids) {
    const std::vector<cg3::Point2d>& points = trapezoidalMap.getPoints();
    const std::vector<Trapezoid>& trapezoids = trapezoidalMap.getTrapezoids();
    bool follow = true;

    size_t id = find(trapezoidalMap, directedAcyclicGraph, segment);

    while (follow) {
        intersectedTrapezoids.push_back(id);

        if (segment.p2().x() <= points[trapezoids[id].getRightPoint()].x())
            follow = false;
        else {
            if (cg3::isPointAtLeft(segment, points[trapezoids[id].getRightPoint()]))
                id = trapezoids[id].getLowerRightNeighbour();
            else
                id = trapezoids[id].getUpperRightNeighbour();

            if (id == std::numeric_limits<size_t>::max())
                follow = false;
        }
    }
}
