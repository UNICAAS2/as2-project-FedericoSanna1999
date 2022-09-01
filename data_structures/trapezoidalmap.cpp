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