#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoidalmap.h"
#include "data_structures/directed_acyclic_graph.h"

namespace algorithms {
    size_t query(const TrapezoidalMap& trapezoidalMap, const DirectedAcyclicGraph& directedAcyclicGraph, const cg3::Point2d& queryPoint);
}

#endif // ALGORITHMS_H
