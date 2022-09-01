#include "directed_acyclic_graph.h"

/**
 * @brief DirectedAcyclicGraph::DirectedAcyclicGraph is the constructor of the class which initializes the vector "nodes".
 */
DirectedAcyclicGraph::DirectedAcyclicGraph() {
    initialize();
}

/**
 * @brief DirectedAcyclicGraph::getNodes returns the vector "nodes".
 * @return the vector "nodes".
 */
const std::vector<Node>& DirectedAcyclicGraph::getNodes() const {
    return nodes;
}

/**
 * @brief DirectedAcyclicGraph::getNode returns the node stored in the vector "nodes" in the position "id".
 * @param id is the node position in the vector "nodes".
 * @return the node stored in the vector "nodes" in the position "id".
 */
const Node& DirectedAcyclicGraph::getNode(const size_t& id) const {
    return nodes[id];
}

/**
 * @brief DirectedAcyclicGraph::getNode returns the node stored in the vector "nodes" in the position "id".
 * @param id is the node position in the vector "nodes".
 * @return the node stored in the vector "nodes" in the position "id".
 */
Node& DirectedAcyclicGraph::getNode(const size_t& id) {
    return nodes[id];
}

/**
 * @brief DirectedAcyclicGraph::clear allows to delete all nodes and re-initialize the vector "nodes".
 */
void DirectedAcyclicGraph::clear() {
    nodes.clear();
    initialize();
}

/**
 * @brief DirectedAcyclicGraph::initialize allows to create the default trapezoid node which represents the bounding box trapezoid.
 */
void DirectedAcyclicGraph::initialize() {
    const Node boundingBoxNode(Node::TRAPEZOID, 0);
    nodes.push_back(boundingBoxNode);
}
