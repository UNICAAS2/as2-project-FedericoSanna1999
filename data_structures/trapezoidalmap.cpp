#include "trapezoidalmap.h"

/**
 * @brief TrapezoidalMap::TrapezoidalMap is the constructor of the class which initializes its vectors to the starting situation.
 * @param boundingBoxMin is the left point of the bounding box trapezoid.
 * @param boundingBoxMax is the right point of the boundin box trapezoid.
 */
TrapezoidalMap::TrapezoidalMap(const cg3::Point2d& boundingBoxMin, const cg3::Point2d& boundingBoxMax) :
    boundingBox(cg3::Point2d(0,0), cg3::Point2d(0,0)) {
    initialize(boundingBoxMin, boundingBoxMax);
}

/**
 * @brief TrapezoidalMap::addPoint allows the new point to be stored if it is not in the vector "points" and returns its position.
 * @param point is the new point.
 * @return the point position in the vector "points".
 */
size_t TrapezoidalMap::addPoint(const cg3::Point2d& point) {
    bool found;
    size_t id = findPoint(point, found);

    bool generalPosition = true;
    if (xCoordSet.find(point.x()) != xCoordSet.end())
        generalPosition = false;


    //Point will be inserted
    if (!found && generalPosition) {
        id = points.size();

        //Add point
        points.push_back(point);

        pointMap.insert(std::make_pair(point, id));
        xCoordSet.insert(point.x());

        //Update bounding box
        boundingBox.setMax(cg3::Point2d(
                std::max(point.x(), boundingBox.max().x()),
                std::max(point.y(), boundingBox.max().y())));
        boundingBox.setMin(cg3::Point2d(
                std::min(point.x(), boundingBox.min().x()),
                std::min(point.y(), boundingBox.min().y())));
    }

    return id;
}

/**
 * @brief TrapezoidalMap::addSegment allows the new segment to be stored.
 * @param segment is the new segment.
 * @return the indexed segment position in the vector "indexedSegments".
 */
size_t TrapezoidalMap::addSegment(const cg3::Segment2d& segment) {
    size_t id;

    cg3::Segment2d orderedSegment = segment;
    if (segment.p2() < segment.p1()) {
        orderedSegment.setP1(segment.p2());
        orderedSegment.setP2(segment.p1());
    }

    bool found;
    findSegment(orderedSegment, found);

    bool degenerate = orderedSegment.p1() == orderedSegment.p2();

    id = std::numeric_limits<size_t>::max();

    if (!degenerate && !found) {
        bool generalPosition = true;

        bool foundPoint1;
        size_t id1 = findPoint(orderedSegment.p1(), foundPoint1);
        bool foundPoint2;
        size_t id2 = findPoint(orderedSegment.p2(), foundPoint2);

        if (!foundPoint1 && xCoordSet.find(orderedSegment.p1().x()) != xCoordSet.end())
            generalPosition = false;

        if (!foundPoint2 && xCoordSet.find(orderedSegment.p2().x()) != xCoordSet.end())
            generalPosition = false;

        if (generalPosition) {
            id = indexedSegments.size();

            if (!foundPoint1)
                id1 = addPoint(orderedSegment.p1());

            if (!foundPoint2)
                id2 = addPoint(orderedSegment.p2());

            IndexedSegment2d indexedSegment(id1, id2);

            indexedSegments.push_back(indexedSegment);

            segmentMap.insert(std::make_pair(indexedSegment, id));
        }
    }

    return id;
}

/**
 * @brief TrapezoidalMap::findPoint returns the point position in the vector "points" if it is stored or null.
 * @param point is the point to be found.
 * @param found is a boolean variable.
 * @return the point position in the vector "points" if it is stored or null.
 */
size_t TrapezoidalMap::findPoint(const cg3::Point2d &point, bool &found) {
    std::unordered_map<cg3::Point2d, size_t>::iterator it = pointMap.find(point);

    //Point already in the data structure
    if (it != pointMap.end()) {
        found = true;
        return it->second;
    }
    //Point not in the data structure
    else {
        found = false;
        return std::numeric_limits<size_t>::max();
    }
}

/**
 * @brief TrapezoidalMap::findSegment returns the indexed segment position in the vector "indexedSegments" if it is stored or null.
 * @param segment is the segment to be found.
 * @param found is a boolean variable.
 * @return the indexed segment position in the vector "indexedSegments" if it is stored or null.
 */
size_t TrapezoidalMap::findSegment(const cg3::Segment2d& segment, bool& found) {
    found = false;

    cg3::Segment2d orderedSegment = segment;
    if (segment.p2() < segment.p1()) {
        orderedSegment.setP1(segment.p2());
        orderedSegment.setP2(segment.p1());
    }

    bool foundPoint1;
    size_t id1 = findPoint(orderedSegment.p1(), foundPoint1);
    if (!foundPoint1)
        return std::numeric_limits<size_t>::max();

    bool foundPoint2;
    size_t id2 = findPoint(orderedSegment.p2(), foundPoint2);
    if (!foundPoint2)
        return std::numeric_limits<size_t>::max();

    return findIndexedSegment(IndexedSegment2d(id1, id2), found);
}

/**
 * @brief TrapezoidalMap::findIndexedSegment returns the indexed segment position in the vector "indexedSegments" if it is stored or null.
 * @param indexedSegment is the indexed segment to be found.
 * @param found is a boolean variable.
 * @return the indexed segment position in the vector "indexedSegments" if it is stored or null.
 */
size_t TrapezoidalMap::findIndexedSegment(const IndexedSegment2d& indexedSegment, bool& found) {
    IndexedSegment2d orderedIndexedSegment = indexedSegment;
    if (indexedSegment.second < indexedSegment.first) {
        orderedIndexedSegment.first = indexedSegment.second;
        orderedIndexedSegment.second = indexedSegment.first;
    }

    std::unordered_map<IndexedSegment2d, size_t>::iterator it = segmentMap.find(orderedIndexedSegment);

    //Segment already in the data structure
    if (it != segmentMap.end()) {
        found = true;
        return it->second;
    }
    //Segment not in the data structure
    else {
        found = false;
        return std::numeric_limits<size_t>::max();
    }
}

/**
 * @brief TrapezoidalMap::getPoints returns the vector "points".
 * @return the vector "points".
 */
const std::vector<cg3::Point2d>& TrapezoidalMap::getPoints() const {
    return points;
}

/**
 * @brief TrapezoidalMap::getPoint returns the point in the vector "points" in the position "id".
 * @param id is the point position in the vector "points".
 * @return the point in the vector "points" in the position "id".
 */
const cg3::Point2d& TrapezoidalMap::getPoint(const size_t& id) const {
    return points[id];
}

/**
 * @brief TrapezoidalMap::getSegment returns the Segment object with the points of the indexed segment in the vector "indexedSegments" in the position "id".
 * @param id is the indexed segment position in the vector "indexedSegments".
 * @return the Segment object with the points of the indexed segment in the vector "indexedSegments" in the position "id".
 */
cg3::Segment2d TrapezoidalMap::getSegment(const size_t& id) const {
    return cg3::Segment2d(points[indexedSegments[id].first], points[indexedSegments[id].second]);
}

/**
 * @brief TrapezoidalMap::getIndexedSegment returns the indexed segment in the vector "indexedSegments" in the position "id".
 * @param id is the indexed segment position in the vector "indexedSegments".
 * @return the indexed segment in the vector "indexedSegments" in the position "id".
 */
const TrapezoidalMap::IndexedSegment2d &TrapezoidalMap::getIndexedSegment(const size_t& id) const {
    return indexedSegments[id];
}

/**
 * @brief TrapezoidalMap::getBoundingBox returns the bounding box.
 * @return the bounding box.
 */
const cg3::BoundingBox2& TrapezoidalMap::getBoundingBox() const {
    return boundingBox;
}

/**
 * @brief TrapezoidalMap::clear allows to delete all points, segments, and trapezoids and re-initialize the vectors to the starting situation.
 */
void TrapezoidalMap::clear() {
    const cg3::Point2d& boundingBoxMin = points[0];
    const cg3::Point2d& boundingBoxMax = points[1];

    points.clear();
    indexedSegments.clear();
    pointMap.clear();
    segmentMap.clear();
    xCoordSet.clear();
    boundingBox.setMin(cg3::Point2d(0,0));
    boundingBox.setMax(cg3::Point2d(0,0));

    trapezoids.clear();
    initialize(boundingBoxMin, boundingBoxMax);
}

/**
 * @brief TrapezoidalMap::update allows the trapezoidal map to be updated when the new segment intersects a trapezoid.
 * @param trapezoidToDelete is the trapezoid index intersected by the segment.
 * @param leftPoint is the left point of the segment which intersects the trapezoid.
 * @param rightPoint is the right point of the segment which intersects the trapezoid.
 * @param segment is the index of the segment which intersects the trapezoid.
 * @param newTrapezoids is the vector which contains the new trapezoids indexes.
 * @param newTrapezoidNodes is the vector which contains the indexes of the new trapezoid nodes.
 * @param leftPointUnshared is a boolean variable which is true when the left point is a new point in the trapezoidal map, otherwise it is false.
 */
void TrapezoidalMap::update(const size_t& trapezoidToDelete, const size_t& leftPoint, const size_t& rightPoint, const size_t& segment, const std::vector<size_t>& newTrapezoids, const std::vector<size_t>& newTrapezoidNodes, const bool& leftPointUnshared) {
    Trapezoid upperTrapezoid(trapezoids[trapezoidToDelete].getTopSegment(), segment, leftPoint, rightPoint, newTrapezoidNodes[0]);
    Trapezoid lowerTrapezoid(segment, trapezoids[trapezoidToDelete].getBottomSegment(), leftPoint, rightPoint, newTrapezoidNodes[1]);
    Trapezoid leftTrapezoid(trapezoids[trapezoidToDelete].getTopSegment(), trapezoids[trapezoidToDelete].getBottomSegment(), trapezoids[trapezoidToDelete].getLeftPoint(), leftPoint, newTrapezoidNodes[2]);
    Trapezoid rightTrapezoid(trapezoids[trapezoidToDelete].getTopSegment(), trapezoids[trapezoidToDelete].getBottomSegment(), rightPoint, trapezoids[trapezoidToDelete].getRightPoint(), newTrapezoidNodes.back());

    if (leftPointUnshared) {
        leftTrapezoid.setUpperRightNeighbour(newTrapezoids[0]);
        leftTrapezoid.setLowerRightNeighbour(newTrapezoids[1]);
        leftTrapezoid.setUpperLeftNeighbour(trapezoids[trapezoidToDelete].getUpperLeftNeighbour());
        leftTrapezoid.setLowerLeftNeighbour(trapezoids[trapezoidToDelete].getLowerLeftNeighbour());
        upperTrapezoid.setUpperLeftNeighbour(newTrapezoids[2]);
        lowerTrapezoid.setLowerLeftNeighbour(newTrapezoids[2]);

        if (leftTrapezoid.getUpperLeftNeighbour() != std::numeric_limits<size_t>::max())
            trapezoids[leftTrapezoid.getUpperLeftNeighbour()].setUpperRightNeighbour(newTrapezoids[2]);

        if (leftTrapezoid.getLowerLeftNeighbour() != std::numeric_limits<size_t>::max())
            trapezoids[leftTrapezoid.getLowerLeftNeighbour()].setLowerRightNeighbour(newTrapezoids[2]);

        if (newTrapezoidNodes.size() != 4) {
            if (getIndexedSegment(upperTrapezoid.getTopSegment()).second != getIndexedSegment(upperTrapezoid.getBottomSegment()).second) {
                upperTrapezoid.setUpperRightNeighbour(trapezoids[trapezoidToDelete].getUpperRightNeighbour());

                if (upperTrapezoid.getUpperRightNeighbour() != std::numeric_limits<size_t>::max())
                    trapezoids[upperTrapezoid.getUpperRightNeighbour()].setUpperLeftNeighbour(newTrapezoids[0]);
            }

            if (getIndexedSegment(lowerTrapezoid.getTopSegment()).second != getIndexedSegment(lowerTrapezoid.getBottomSegment()).second) {
                lowerTrapezoid.setLowerRightNeighbour(trapezoids[trapezoidToDelete].getLowerRightNeighbour());

                if (lowerTrapezoid.getLowerRightNeighbour() != std::numeric_limits<size_t>::max())
                    trapezoids[lowerTrapezoid.getLowerRightNeighbour()].setLowerLeftNeighbour(newTrapezoids[1]);
            }
        }

    } else {
        if (getIndexedSegment(upperTrapezoid.getTopSegment()).first != getIndexedSegment(upperTrapezoid.getBottomSegment()).first) {
            upperTrapezoid.setUpperLeftNeighbour(trapezoids[trapezoidToDelete].getUpperLeftNeighbour());

            if (upperTrapezoid.getUpperLeftNeighbour() != std::numeric_limits<size_t>::max())
                trapezoids[upperTrapezoid.getUpperLeftNeighbour()].setUpperRightNeighbour(newTrapezoids[0]);
        }

        if (getIndexedSegment(lowerTrapezoid.getTopSegment()).first != getIndexedSegment(lowerTrapezoid.getBottomSegment()).first) {
            lowerTrapezoid.setLowerLeftNeighbour(trapezoids[trapezoidToDelete].getLowerLeftNeighbour());

            if (lowerTrapezoid.getLowerLeftNeighbour() != std::numeric_limits<size_t>::max())
                trapezoids[lowerTrapezoid.getLowerLeftNeighbour()].setLowerRightNeighbour(newTrapezoids[1]);
        }
    }

    if (!leftPointUnshared || newTrapezoids.size() == 4) {
        rightTrapezoid.setUpperLeftNeighbour(newTrapezoids[0]);
        rightTrapezoid.setLowerLeftNeighbour(newTrapezoids[1]);
        rightTrapezoid.setUpperRightNeighbour(trapezoids[trapezoidToDelete].getUpperRightNeighbour());
        rightTrapezoid.setLowerRightNeighbour(trapezoids[trapezoidToDelete].getLowerRightNeighbour());
        upperTrapezoid.setUpperRightNeighbour(newTrapezoids.back());
        lowerTrapezoid.setLowerRightNeighbour(newTrapezoids.back());

        if (rightTrapezoid.getUpperRightNeighbour() != std::numeric_limits<size_t>::max())
            trapezoids[rightTrapezoid.getUpperRightNeighbour()].setUpperLeftNeighbour(newTrapezoids.back());

        if (rightTrapezoid.getLowerRightNeighbour() != std::numeric_limits<size_t>::max())
            trapezoids[rightTrapezoid.getLowerRightNeighbour()].setLowerLeftNeighbour(newTrapezoids.back());
    }

    trapezoids[trapezoidToDelete] = upperTrapezoid;

    trapezoids.push_back(lowerTrapezoid);

    if (leftPointUnshared) {
        trapezoids.push_back(leftTrapezoid);

        if (newTrapezoidNodes.size() == 4)
            trapezoids.push_back(rightTrapezoid);
    } else
        trapezoids.push_back(rightTrapezoid);
}

/**
 * @brief TrapezoidalMap::update allows the trapezoidal map to be updated when the new segment intersects more trapezoids.
 * @param trapezoidsToDelete is the vector which contains the indexes of the intersected trapezoids.
 * @param leftPoint is the left point of the segment which intersects the trapezoids.
 * @param rightPoint is the right point of the segment which intersects the trapezoids.
 * @param segment is the index of the segment which intersects the trapezoids.
 * @param newTrapezoids is the vector which contains the new trapezoids indexes.
 * @param newTrapezoidNodes is the vector which contains the indexes of the new trapezoid nodes.
 * @param above is the vector which contains boolean variables which indicate for each trapezoid to be deleted whether it is above the segment.
 */
void TrapezoidalMap::update(const std::vector<size_t>& trapezoidsToDelete, const size_t& leftPoint, const size_t& rightPoint, const size_t& segment, const std::vector<size_t>& newTrapezoids, const std::vector<size_t>& newTrapezoidNodes, const std::vector<bool>& above) {
    // store the index of the first intersected trapezoid
    const size_t& front = trapezoidsToDelete.front();

    // store the index of the last intersected trapezoid
    const size_t& back = trapezoidsToDelete.back();

    // store the index of the possible right trapezoid
    const size_t& lastTrapezoidId = newTrapezoids[newTrapezoids.size() - 2];

    std::vector<size_t>::const_iterator trapezoidNodeToAssign = newTrapezoidNodes.cbegin();

    // create the new trapezoid to the left of the left point of the segment
    Trapezoid leftTrapezoid(trapezoids[front].getTopSegment(), trapezoids[front].getBottomSegment(), trapezoids[front].getLeftPoint(), leftPoint, *trapezoidNodeToAssign);

    // if the left point of the segment is a new point
    if (leftPoint != std::numeric_limits<size_t>::max()) {
        // reference the next trapezoid node to assign
        trapezoidNodeToAssign++;

        // the left point of the segment is the new left point of the first intersected trapezoid
        trapezoids[front].setLeftPoint(leftPoint);

        // update upper neighbours of the new left trapezoid
        if (trapezoids[front].getUpperLeftNeighbour() != std::numeric_limits<size_t>::max()) {
            leftTrapezoid.setUpperLeftNeighbour(trapezoids[front].getUpperLeftNeighbour());
            trapezoids[leftTrapezoid.getUpperLeftNeighbour()].setUpperRightNeighbour(newTrapezoids[0]);
        }

        // update lower neighbours of the new left trapezoid
        if (trapezoids[front].getLowerLeftNeighbour() != std::numeric_limits<size_t>::max()) {
            leftTrapezoid.setLowerLeftNeighbour(trapezoids[front].getLowerLeftNeighbour());
            trapezoids[leftTrapezoid.getLowerLeftNeighbour()].setLowerRightNeighbour(newTrapezoids[0]);
        }

        // update neighbours of the first intersected trapezoid
        trapezoids[front].setUpperLeftNeighbour(newTrapezoids[0]);
        trapezoids[front].setLowerLeftNeighbour(newTrapezoids[0]);

        // the new left trapezoid is stored
        trapezoids.push_back(leftTrapezoid);
    }

    // create the new trapezoid to the right of the right point of the segment
    Trapezoid rightTrapezoid(trapezoids[back].getTopSegment(), trapezoids[back].getBottomSegment(), rightPoint, trapezoids[back].getRightPoint(), *trapezoidNodeToAssign);

    // if the right point of the segment is a new point
    if (rightPoint != std::numeric_limits<size_t>::max()) {
        // reference the next trapezoid node to assign
        trapezoidNodeToAssign++;

        // the right point of the segment is the new right point of the last intersected trapezoid
        trapezoids[back].setRightPoint(rightPoint);

        // update upper neighbours of the new right trapezoid
        if (trapezoids[back].getUpperRightNeighbour() != std::numeric_limits<size_t>::max()) {
            rightTrapezoid.setUpperRightNeighbour(trapezoids[back].getUpperRightNeighbour());
            trapezoids[rightTrapezoid.getUpperRightNeighbour()].setUpperLeftNeighbour(lastTrapezoidId);
        }

        // update lower neighbours of the new right trapezoid
        if (trapezoids[back].getLowerRightNeighbour() != std::numeric_limits<size_t>::max()) {
            rightTrapezoid.setLowerRightNeighbour(trapezoids[back].getLowerRightNeighbour());
            trapezoids[rightTrapezoid.getLowerRightNeighbour()].setLowerLeftNeighbour(lastTrapezoidId);
        }

        // update neighbours of the last intersected trapezoid
        trapezoids[back].setUpperRightNeighbour(lastTrapezoidId);
        trapezoids[back].setLowerRightNeighbour(lastTrapezoidId);

        // the new right trapezoid is stored
        trapezoids.push_back(rightTrapezoid);
    }
}

/**
 * @brief TrapezoidalMap::getTrapezoids returns the vector "trapezoids".
 * @return the vector "trapezoids".
 */
const std::vector<Trapezoid>& TrapezoidalMap::getTrapezoids() const {
    return trapezoids;
}

/**
 * @brief TrapezoidalMap::getTrapezoid returns the trapezoid stored in the vector "trapezoids" in the position "id".
 * @param id is the trapezoid position in the vector "trapezoids".
 * @return the trapezoid stored in the vector "trapezoids" in the position "id"
 */
const Trapezoid& TrapezoidalMap::getTrapezoid(const size_t& id) const {
    return trapezoids[id];
}

/**
 * @brief TrapezoidalMap::getTrapezoid returns the trapezoid stored in the vector "trapezoids" in the position "id".
 * @param id is the trapezoid position in the vector "trapezoids".
 * @return the trapezoid stored in the vector "trapezoids" in the position "id"
 */
Trapezoid& TrapezoidalMap::getTrapezoid(const size_t& id) {
    return trapezoids[id];
}

/**
 * @brief TrapezoidalMap::initialize allows to create the default trapezoid which represents the bounding box trapezoid.
 * @param boundingBoxMin is the left point.
 * @param boundingBoxMax is the right point.
 */
void TrapezoidalMap::initialize(const cg3::Point2d& boundingBoxMin, const cg3::Point2d& boundingBoxMax) {
    const size_t& leftPoint = addPoint(boundingBoxMin);
    const size_t& rightPoint = addPoint(boundingBoxMax);
    const Trapezoid boundingBoxTrapezoid(std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), leftPoint, rightPoint, 0);
    trapezoids.push_back(boundingBoxTrapezoid);
}
