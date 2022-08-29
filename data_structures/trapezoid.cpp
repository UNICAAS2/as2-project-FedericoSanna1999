#include "trapezoid.h"

/**
 * @brief Trapezoid::Trapezoid is the constructor of the class which allows a top and a bottom segment, a left and a right point and a node to be assigned, while neighbours are null by default.
 * @param topSegment is the index in the vector "segments" in which it is stored.
 * @param bottomSegment is the index in the vector "segments" in which it is stored.
 * @param leftPoint is the index in the vector "points" in which it is stored.
 * @param rightPoint is the index in the vector "points" in which it is stored.
 * @param node is the index in the vector "nodes" in which it is stored.
 */
Trapezoid::Trapezoid(const size_t& topSegment, const size_t& bottomSegment, const size_t& leftPoint, const size_t& rightPoint, const size_t& node) :
    topSegment(topSegment), bottomSegment(bottomSegment), leftPoint(leftPoint), rightPoint(rightPoint), node(node) {

}

/**
 * @brief Trapezoid::getTopSegment returns the index in the vector "segments" in which it is stored.
 * @return the index in the vector "segments" in which it is stored.
 */
size_t Trapezoid::getTopSegment() const {
    return topSegment;
}

/**
 * @brief Trapezoid::getBottomSegment returns the index in the vector "segments" in which it is stored.
 * @return the index in the vector "segments" in which it is stored.
 */
size_t Trapezoid::getBottomSegment() const {
    return bottomSegment;
}

/**
 * @brief Trapezoid::getLeftPoint returns the index in the vector "points" in which it is stored.
 * @return the index in the vector "points" in which it is stored.
 */
size_t Trapezoid::getLeftPoint() const {
    return leftPoint;
}

/**
 * @brief Trapezoid::getRightPoint returns the index in the vector "points" in which it is stored.
 * @return the index in the vector "points" in which it is stored.
 */
size_t Trapezoid::getRightPoint() const {
    return rightPoint;
}

/**
 * @brief Trapezoid::getNode returns the index in the vector "nodes" in which it is stored.
 * @return the index in the vector "nodes" in which it is stored.
 */
size_t Trapezoid::getNode() const {
    return node;
}

/**
 * @brief Trapezoid::getUpperLeftNeighbour returns the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 * @return the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
size_t Trapezoid::getUpperLeftNeighbour() const {
    return upperLeftNeighbour;
}

/**
 * @brief Trapezoid::getUpperRightNeighbour returns the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 * @return the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
size_t Trapezoid::getUpperRightNeighbour() const {
    return upperRightNeighbour;
}

/**
 * @brief Trapezoid::getLowerLeftNeighbour returns the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 * @return the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
size_t Trapezoid::getLowerLeftNeighbour() const {
    return lowerLeftNeighbour;
}

/**
 * @brief Trapezoid::getLowerRightNeighbour returns the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 * @return the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
size_t Trapezoid::getLowerRightNeighbour() const {
    return lowerRightNeighbour;
}

/**
 * @brief Trapezoid::setTopSegment allows to assign a top segment.
 * @param topSegment is the index in the vector "segments" in which it is stored.
 */
void Trapezoid::setTopSegment(const size_t& topSegment) {
    this->topSegment = topSegment;
}

/**
 * @brief Trapezoid::setBottomSegment allows to assign a bottom segment.
 * @param bottomSegment is the index in the vector "segments" in which it is stored.
 */
void Trapezoid::setBottomSegment(const size_t& bottomSegment) {
    this->bottomSegment = bottomSegment;
}

/**
 * @brief Trapezoid::setLeftPoint allows to assign a left point.
 * @param leftPoint is the index in the vector "points" in which it is stored.
 */
void Trapezoid::setLeftPoint(const size_t& leftPoint) {
    this->leftPoint = leftPoint;
}

/**
 * @brief Trapezoid::setRightPoint allows to assign a right point.
 * @param rightPoint is the index in the vector "points" in which it is stored.
 */
void Trapezoid::setRightPoint(const size_t& rightPoint) {
    this->rightPoint = rightPoint;
}

/**
 * @brief Trapezoid::setNode allows to assign a node.
 * @param node is the index in the vector "nodes" in which it is stored.
 */
void Trapezoid::setNode(const size_t& node) {
    this->node = node;
}

/**
 * @brief Trapezoid::setUpperLeftNeighbour allows to assign an upper left neighbour.
 * @param upperLeftNeighbour is the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
void Trapezoid::setUpperLeftNeighbour(const size_t& upperLeftNeighbour) {
    this->upperLeftNeighbour = upperLeftNeighbour;
}

/**
 * @brief Trapezoid::setUpperRightNeighbour allows to assign an upper right neighbour.
 * @param upperRightNeighbour is the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
void Trapezoid::setUpperRightNeighbour(const size_t& upperRightNeighbour) {
    this->upperRightNeighbour = upperRightNeighbour;
}

/**
 * @brief Trapezoid::setLowerLeftNeighbour allows to assign a lower left neighbour.
 * @param lowerLeftNeighbour is the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
void Trapezoid::setLowerLeftNeighbour(const size_t& lowerLeftNeighbour) {
    this->lowerLeftNeighbour = lowerLeftNeighbour;
}

/**
 * @brief Trapezoid::setLowerRightNeighbour allows to assign a lower right neighbour.
 * @param lowerRightNeighbour is the index in the vector "trapezoids" in which it is stored or a specific value which represents null.
 */
void Trapezoid::setLowerRightNeighbour(const size_t& lowerRightNeighbour) {
    this->lowerRightNeighbour = lowerRightNeighbour;
}
