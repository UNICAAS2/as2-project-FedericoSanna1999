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

    void update(const size_t& nodeToDelete, const size_t& leftPoint, const size_t& rightPoint, const size_t& segment, const std::vector<size_t>& newTrapezoids, std::vector<size_t>& newTrapezoidNodes, const bool& leftPointUnshared);
    void update(std::vector<size_t>& nodesToDelete, const size_t& leftPoint, const size_t& rightPoint, const size_t& segment, const std::vector<size_t>& newTrapezoids, std::vector<size_t>& newTrapezoidNodes, std::vector<size_t>& leftChildren, std::vector<size_t>& rightChildren);

    const std::vector<Node>& getNodes() const;
    const Node& getNode(const size_t& id) const;
    Node& getNode(const size_t& id);

    void clear();

private:
    void initialize();

    std::vector<Node> nodes;
};

#endif // DIRECTED_ACYCLIC_GRAPH_H
