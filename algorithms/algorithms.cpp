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

    if (intersectedTrapezoids.size() == 1)
        update(trapezoidalMap, directedAcyclicGraph, id, intersectedTrapezoids[0]);
    else
        update(trapezoidalMap, directedAcyclicGraph, id, intersectedTrapezoids);
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

/**
 * @brief algorithms::update allows the trapezoidal map and the directed acyclic graph to be updated when a segment intersects a trapezoid.
 * @param trapezoidalMap contains all points, segments, and trapezoids.
 * @param directedAcyclicGraph contains all point, segment, and trapezoid nodes.
 * @param segment is the segment which intersects the trapezoid.
 * @param intersectedTrapezoid is the trapezoid intersected by the segment.
 */
void algorithms::update(TrapezoidalMap& trapezoidalMap, DirectedAcyclicGraph& directedAcyclicGraph, const size_t& segment, const size_t& intersectedTrapezoid) {
    const std::vector<Trapezoid>& trapezoids = trapezoidalMap.getTrapezoids();
    const TrapezoidalMap::IndexedSegment2d& indexedSegment = trapezoidalMap.getIndexedSegment(segment);

    // indexes of the new trapezoids (minimum 3)
    std::vector<size_t> newTrapezoids = {intersectedTrapezoid, trapezoids.size(), trapezoids.size() + 1};
    std::vector<size_t> newTrapezoidNodes;
    const bool leftPointUnshared = indexedSegment.first != trapezoids[intersectedTrapezoid].getLeftPoint();

    // add a fourth index for a new trapezoid if the segment points are new
    if (leftPointUnshared && indexedSegment.second != trapezoids[intersectedTrapezoid].getRightPoint())
        newTrapezoids.push_back(trapezoids.size() + 2);

    directedAcyclicGraph.update(trapezoids[intersectedTrapezoid].getNode(), indexedSegment.first, indexedSegment.second, segment, newTrapezoids, newTrapezoidNodes, leftPointUnshared);
    trapezoidalMap.update(intersectedTrapezoid, indexedSegment.first, indexedSegment.second, segment, newTrapezoids, newTrapezoidNodes, leftPointUnshared);
}

/**
 * @brief algorithms::update allows the trapezoidal map and the directed acyclic graph to be updated when a segment intersects more trapezoids.
 * @param trapezoidalMap contains all points, segments, and trapezoids.
 * @param directedAcyclicGraph contains all point, segment, and trapezoid nodes.
 * @param segment is the segment which intersects the trapezoids.
 * @param intersectedTrapezoids is the vector of trapezoids intersected by the segment.
 */
void algorithms::update(TrapezoidalMap &trapezoidalMap, DirectedAcyclicGraph &directedAcyclicGraph, const size_t& segment, const std::vector<size_t>& intersectedTrapezoids) {
    const std::vector<cg3::Point2d>& points = trapezoidalMap.getPoints();
    const std::vector<Trapezoid>& trapezoids = trapezoidalMap.getTrapezoids();
    const TrapezoidalMap::IndexedSegment2d& indexedSegment = trapezoidalMap.getIndexedSegment(segment);

    // leftPoint is null if the point already exists, else it is the segment's left point.
    const size_t& leftPoint = (trapezoids[intersectedTrapezoids.front()].getLeftPoint() == indexedSegment.first) ? std::numeric_limits<size_t>::max() : indexedSegment.first;

    // rightPoint is null if the point already exists, else it is the segment's right point.
    const size_t& rightPoint = (trapezoids[intersectedTrapezoids.back()].getRightPoint() == indexedSegment.second) ? std::numeric_limits<size_t>::max() : indexedSegment.second;

    std::vector<size_t> newTrapezoids = {trapezoids.size()};
    std::vector<size_t> newTrapezoidNodes;
    std::vector<size_t> nodesToDelete, leftChildren, rightChildren;
    std::vector<bool> above;

    // if leftPoint is not null, the first trapezoid intersected by the segment is divided into 3 trapezoids.
    if (leftPoint == indexedSegment.first)
        newTrapezoids.push_back(trapezoids.size() + 1);

    // if rightPoint is not null, the last trapezoid intersected by the segment is divided into 3 trapezoids.
    if (rightPoint == indexedSegment.second)
        newTrapezoids.push_back(trapezoids.size() + newTrapezoids.size());

    for (const size_t& trapezoid : intersectedTrapezoids) {
        // store node index of the trapezoid intersected by the segment.
        nodesToDelete.push_back(trapezoids[trapezoid].getNode());

        // check if the right point (left point only for the last trapezoid intersected) is at left of the segment.
        const size_t& queryPoint = (trapezoid == intersectedTrapezoids.back()) ? trapezoids[trapezoid].getLeftPoint() : trapezoids[trapezoid].getRightPoint();
        above.push_back(cg3::isPointAtLeft(points[indexedSegment.first], points[indexedSegment.second], points[queryPoint]));

        // if the trapezoid is above of the segment, the trapezoid is the left child of the new segment nodes in the directed acyclic graph, otherwise it is the right one.
        if (above.back())
            while (leftChildren.size() < nodesToDelete.size())
                leftChildren.push_back(trapezoids[trapezoid].getNode());
        else
            while (rightChildren.size() < nodesToDelete.size())
                rightChildren.push_back(trapezoids[trapezoid].getNode());
    }

    // fill the vectors "leftChildren" and "rightChildren" with a null values for missing children
    while (leftChildren.size() < nodesToDelete.size())
        leftChildren.push_back(std::numeric_limits<size_t>::max());

    while (rightChildren.size() < nodesToDelete.size())
        rightChildren.push_back(std::numeric_limits<size_t>::max());

    directedAcyclicGraph.update(nodesToDelete, leftPoint, rightPoint, segment, newTrapezoids, newTrapezoidNodes, leftChildren, rightChildren);
    trapezoidalMap.update(intersectedTrapezoids, leftPoint, rightPoint, segment, newTrapezoids, newTrapezoidNodes, above);
}
