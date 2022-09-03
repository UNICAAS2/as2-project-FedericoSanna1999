#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoidalmap.h"
#include "data_structures/directed_acyclic_graph.h"

namespace algorithms {
    size_t query(const TrapezoidalMap& trapezoidalMap, const DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Point2d& queryPoint);

    size_t find(const TrapezoidalMap& trapezoidalMap, const DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Segment2d& segment);
    void followSegment(const TrapezoidalMap& trapezoidalMap, const DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Segment2d& segment, std::vector<size_t>& intersectedTrapezoids);
}

#endif // ALGORITHMS_H
