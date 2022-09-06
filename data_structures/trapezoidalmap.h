#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>
#include <cg3/geometry/bounding_box2.h>
#include "trapezoid.h"

/**
 * @brief The TrapezoidalMap class allows to store segments, with indexed non-duplicates point, and trapezoids.
 */
class TrapezoidalMap {

public:
    typedef std::pair<size_t, size_t> IndexedSegment2d;

    TrapezoidalMap(const cg3::Point2d& boundingBoxMin, const cg3::Point2d& boundingBoxMax);

    size_t addPoint(const cg3::Point2d& point);
    size_t addSegment(const cg3::Segment2d& segment);

    size_t findPoint(const cg3::Point2d& point, bool& found);
    size_t findSegment(const cg3::Segment2d& segment, bool& found);
    size_t findIndexedSegment(const IndexedSegment2d& indexedSegment, bool& found);

    const std::vector<cg3::Point2d>& getPoints() const;
    const cg3::Point2d& getPoint(const size_t& id) const;

    cg3::Segment2d getSegment(const size_t& id) const;

    const IndexedSegment2d& getIndexedSegment(const size_t& id) const;

    const cg3::BoundingBox2& getBoundingBox() const;

    void clear();

    void update(const size_t& trapezoidToDelete, const size_t& leftPoint, const size_t& rightPoint, const size_t& segment, const std::vector<size_t>& newTrapezoids, const std::vector<size_t>& newTrapezoidNodes, const bool& leftPointUnshared);

    const std::vector<Trapezoid>& getTrapezoids() const;
    const Trapezoid& getTrapezoid(const size_t& id) const;
    Trapezoid& getTrapezoid(const size_t& id);

private:
    void initialize(const cg3::Point2d& boundingBoxMin, const cg3::Point2d& boundingBoxMax);

    std::vector<cg3::Point2d> points;
    std::vector<IndexedSegment2d> indexedSegments;

    std::unordered_map<cg3::Point2d, size_t> pointMap;
    std::unordered_map<IndexedSegment2d, size_t> segmentMap;
    std::unordered_set<double> xCoordSet;

    cg3::BoundingBox2 boundingBox;

    std::vector<Trapezoid> trapezoids;

};

#endif // TRAPEZOIDALMAP_H
