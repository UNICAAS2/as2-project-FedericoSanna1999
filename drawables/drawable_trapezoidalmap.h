#ifndef DRAWABLE_TRAPEZOIDALMAP_H
#define DRAWABLE_TRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"
#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/utilities/color.h>

/**
 * @brief The DrawableTrapezoidalMap class allows drawing trapezoids and vertical lines and highlighting the query output trapezoid.
 */
class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject {

public:
    DrawableTrapezoidalMap(const cg3::Point2d& boundingBoxMin, const cg3::Point2d& boundingBoxMax);

    void draw() const;
    cg3::Point3d sceneCenter() const;
    double sceneRadius() const;

    void highlight(const size_t& lastTrapezoidFound);
    void addTrapezoidColors();
    void clear();

private:
    void initialize();

    const cg3::Color highlightColor = cg3::Color(0, 0, 0);
    std::vector<cg3::Color> trapezoidColors;
    size_t lastTrapezoidFound = std::numeric_limits<size_t>::max();

};

#endif // DRAWABLE_TRAPEZOIDALMAP_H
