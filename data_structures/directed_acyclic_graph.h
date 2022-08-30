#ifndef DIRECTED_ACYCLIC_GRAPH_H
#define DIRECTED_ACYCLIC_GRAPH_H

#include <vector>
#include "node.h"

/**
 * @brief The DirectedAcyclicGraph class allows all nodes to be stored. Internal nodes contain points or segments, while leaves contain trapezoids.
 * They can be connected to other nodes using the leftChild or rightChild attribute of the class Node.
 */
class DirectedAcyclicGraph {

public:
    DirectedAcyclicGraph();

    const std::vector<Node>& getNodes() const;
    const Node& getNode(const size_t& id) const;
    Node& getNode(const size_t& id);

    void clear();

private:
    void initialize();

    std::vector<Node> nodes;
};

#endif // DIRECTED_ACYCLIC_GRAPH_H
