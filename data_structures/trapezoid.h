#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cstddef>
#include <limits>

/**
 * @brief The Trapezoid class allows to create trapezoids which can store:
 * - a top segment as an index in the vector "segments" in which it is stored;
 * - a bottom segment as an index in the vector "segments" in which it is stored;
 * - a left point as an index in the vector "points" in which it is stored;
 * - a right point as an index in the vector "points" in which it is stored;
 * - a node as an index in the vector "nodes" in which it is stored;
 * - an upper left neighbour as an index in the vector "trapezoids" in which it is stored or a specific value which represents null;
 * - an upper right neighbour as an index in the vector "trapezoids" in which it is stored or a specific value which represents null;
 * - a lower left neighbour as an index in the vector "trapezoids" in which it is stored or a specific value which represents null;
 * - a lower right neighbour as an index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 * std::numeric_limits<size_t>::max() represents null.
 */
class Trapezoid {

public:
    Trapezoid(const size_t& topSegment, const size_t& bottomSegment, const size_t& leftPoint, const size_t& rightPoint, const size_t& node);

    size_t getTopSegment() const;
    size_t getBottomSegment() const;
    size_t getLeftPoint() const;
    size_t getRightPoint() const;

    size_t getNode() const;

    size_t getUpperLeftNeighbour() const;
    size_t getUpperRightNeighbour() const;
    size_t getLowerLeftNeighbour() const;
    size_t getLowerRightNeighbour() const;

    void setTopSegment(const size_t& topSegment);
    void setBottomSegment(const size_t& bottomSegment);
    void setLeftPoint(const size_t& leftPoint);
    void setRightPoint(const size_t& rightPoint);

    void setNode(const size_t& node);

    void setUpperLeftNeighbour(const size_t& upperLeftNeighbour);
    void setUpperRightNeighbour(const size_t& upperRightNeighbour);
    void setLowerLeftNeighbour(const size_t& lowerLeftNeighbour);
    void setLowerRightNeighbour(const size_t& lowerRightNeighbour);

private:
    size_t topSegment;
    size_t bottomSegment;
    size_t leftPoint;
    size_t rightPoint;

    size_t node;

    size_t upperLeftNeighbour = std::numeric_limits<size_t>::max();
    size_t upperRightNeighbour = std::numeric_limits<size_t>::max();
    size_t lowerLeftNeighbour = std::numeric_limits<size_t>::max();
    size_t lowerRightNeighbour = std::numeric_limits<size_t>::max();

};

#endif // TRAPEZOID_H
