#include "drawable_trapezoidalmap.h"

#include <cg3/viewer/opengl_objects/opengl_objects2.h>

/**
 * @brief DrawableTrapezoidalMap::DrawableTrapezoidalMap is the constructor of the class which initializes the trapezoidal map.
 * @param boundingBoxMin is the left point of the bounding box trapezoid.
 * @param boundingBoxMax is the right point of the bounding box trapezoid.
 */
DrawableTrapezoidalMap::DrawableTrapezoidalMap(const cg3::Point2d& boundingBoxMin, const cg3::Point2d& boundingBoxMax) :
    TrapezoidalMap(boundingBoxMin, boundingBoxMax) {
    initialize();
}

/**
 * @brief DrawableTrapezoidalMap::draw allows drawing trapezoids and vertical lines and highlighting the query output trapezoid.
 */
void DrawableTrapezoidalMap::draw() const {
    // TODO
}

/**
 * @brief DrawableTrapezoidalMap::sceneCenter returns the 3D point which is the center point.
 * @return the 3D point which is the center point.
 */
cg3::Point3d DrawableTrapezoidalMap::sceneCenter() const {
    return cg3::Point3d(getBoundingBox().center().x(), getBoundingBox().center().y(), 0);
}

/**
 * @brief DrawableTrapezoidalMap::sceneRadius returns the length of the diagonal of the bounding box.
 * @return the length of the diagonal of the bounding box.
 */
double DrawableTrapezoidalMap::sceneRadius() const {
    return getBoundingBox().diag();
}

/**
 * @brief DrawableTrapezoidalMap::highlight allows storing the index of the last trapezoid found after the query.
 * @param lastTrapezoidFound is the index of the last trapezoid found after the query.
 */
void DrawableTrapezoidalMap::highlight(const size_t& lastTrapezoidFound) {
    this->lastTrapezoidFound = lastTrapezoidFound;
}

/**
 * @brief DrawableTrapezoidalMap::addTrapezoidColors allows adding new random colors in the vector "trapezoidColors" for the new trapezoids after a new segment insertion.
 */
void DrawableTrapezoidalMap::addTrapezoidColors() {
    // TODO
}

/**
 * @brief DrawableTrapezoidalMap::clear allows to clear and re-initialize the trapezoidal map and the vector "trapezoidColors".
 */
void DrawableTrapezoidalMap::clear() {
    TrapezoidalMap::clear();
    trapezoidColors.clear();
    initialize();
}

/**
 * @brief DrawableTrapezoidalMap::initialize allows to initialize the vector "trapezoidColors" and set the index of the last trapezoid found to null.
 */
void DrawableTrapezoidalMap::initialize() {
    const cg3::Color boundingBoxColor(255, 255, 255);
    trapezoidColors.push_back(boundingBoxColor);
    lastTrapezoidFound = std::numeric_limits<size_t>::max();
}
