#include "drawable_trapezoidalmap.h"

#include <cg3/viewer/opengl_objects/opengl_objects2.h>
#include "utils/geometric_utils.h"

/**
 * @brief DrawableTrapezoidalMap::DrawableTrapezoidalMap is the constructor of the class which initializes the trapezoidal map.
 * @param boundingBoxMin is the left point of the bounding box trapezoid.
 * @param boundingBoxMax is the right point of the bounding box trapezoid.
 */
DrawableTrapezoidalMap::DrawableTrapezoidalMap(const cg3::Point2d& boundingBoxMin, const cg3::Point2d& boundingBoxMax) :
    TrapezoidalMap(boundingBoxMin, boundingBoxMax) {
    std::srand(time(nullptr));
    initialize();
}

/**
 * @brief DrawableTrapezoidalMap::draw allows drawing trapezoids and vertical lines and highlighting the query output trapezoid.
 */
void DrawableTrapezoidalMap::draw() const {
    const std::vector<cg3::Point2d>& points = getPoints();
    const std::vector<Trapezoid>& trapezoids = getTrapezoids();

    const cg3::Color verticalLineColor(255, 0, 0);

    const cg3::Segment2d boundingBoxTopSegment(cg3::Point2d(points[0].x(), points[1].y()), points[1]);
    const cg3::Segment2d boundingBoxBottomSegment(points[0], cg3::Point2d(points[1].x(), points[0].y()));

    for (size_t id = 0; id < trapezoids.size(); id++) {
        const cg3::Segment2d& topSegment = (trapezoids[id].getTopSegment() == std::numeric_limits<size_t>::max()) ? boundingBoxTopSegment : getSegment(trapezoids[id].getTopSegment());
        const cg3::Segment2d& bottomSegment = (trapezoids[id].getBottomSegment() == std::numeric_limits<size_t>::max()) ? boundingBoxBottomSegment : getSegment(trapezoids[id].getBottomSegment());

        const cg3::Point2d& lowerLeftPoint = geometricUtils::intersection(bottomSegment, points[trapezoids[id].getLeftPoint()].x());
        const cg3::Point2d& upperLeftPoint = geometricUtils::intersection(topSegment, points[trapezoids[id].getLeftPoint()].x());
        const cg3::Point2d& upperRightPoint = geometricUtils::intersection(topSegment, points[trapezoids[id].getRightPoint()].x());
        const cg3::Point2d& lowerRightPoint = geometricUtils::intersection(bottomSegment, points[trapezoids[id].getRightPoint()].x());

        if (trapezoids[id].getLeftPoint() != 0)
            cg3::opengl::drawLine2(lowerLeftPoint, upperLeftPoint, verticalLineColor);

        if (trapezoids[id].getRightPoint() != 1)
            cg3::opengl::drawLine2(lowerRightPoint, upperRightPoint, verticalLineColor);

        glBegin(GL_POLYGON);

        if (lastTrapezoidFound == id)
            glColor3d(highlightColor.red() / 255.0, highlightColor.green() / 255.0, highlightColor.blue() / 255.0);
        else
            glColor3d(trapezoidColors[id].red() / 255.0, trapezoidColors[id].green() / 255.0, trapezoidColors[id].blue() / 255.0);

        glVertex2d(lowerLeftPoint.x(), lowerLeftPoint.y());
        glVertex2d(upperLeftPoint.x(), upperLeftPoint.y());
        glVertex2d(upperRightPoint.x(), upperRightPoint.y());
        glVertex2d(lowerRightPoint.x(), lowerRightPoint.y());

        glEnd();
    }
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
    const size_t& trapezoidNumber = getTrapezoids().size();
    cg3::Color trapezoidColor;

    while (trapezoidColors.size() < trapezoidNumber) {
        do {
            trapezoidColor = cg3::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        } while (trapezoidColor == highlightColor);

        trapezoidColors.push_back(trapezoidColor);
    }
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
