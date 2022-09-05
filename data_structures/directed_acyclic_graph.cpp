#include "directed_acyclic_graph.h"

/**
 * @brief DirectedAcyclicGraph::DirectedAcyclicGraph is the constructor of the class which initializes the vector "nodes".
 */
DirectedAcyclicGraph::DirectedAcyclicGraph() {
    initialize();
}

/**
 * @brief DirectedAcyclicGraph::update allows the directed acyclic graph to be updated when a segment intersects a trapezoid.
 * @param nodeToDelete is the node of the trapezoid intersected by the segment.
 * @param leftPoint is the left point of the segment which intersects the trapezoid.
 * @param rightPoint is the right point of the segment which intersects the trapezoid.
 * @param segment is the index of the segment which intersects the trapezoid.
 * @param newTrapezoids is the vector which contains the new trapezoids indexes.
 * @param newTrapezoidNodes is the vector which contains the indexes of the new trapezoid nodes.
 * @param leftPointUnshared is a boolean variable which is true when the left point is a new point in the trapezoidal map, otherwise it is false.
 */
void DirectedAcyclicGraph::update(const size_t& nodeToDelete, const size_t& leftPoint, const size_t& rightPoint, const size_t& segment, const std::vector<size_t>& newTrapezoids, std::vector<size_t>& newTrapezoidNodes, const bool& leftPointUnshared) {
    const Node upperTrapezoidNode(Node::TRAPEZOID, newTrapezoids[0]);
    const Node lowerTrapezoidNode(Node::TRAPEZOID, newTrapezoids[1]);

    Node segmentNode(Node::SEGMENT, segment);

    segmentNode.setLeftChild(nodes.size());
    newTrapezoidNodes.push_back(nodes.size());
    nodes.push_back(upperTrapezoidNode);

    segmentNode.setRightChild(nodes.size());
    newTrapezoidNodes.push_back(nodes.size());
    nodes.push_back(lowerTrapezoidNode);

    Node rightPointNode(Node::POINT, rightPoint);

    rightPointNode.setLeftChild(nodes.size());
    nodes.push_back(segmentNode);

    Node leftPointNode(Node::POINT, leftPoint);

    if (leftPointUnshared) {
        const Node leftTrapezoidNode(Node::TRAPEZOID, newTrapezoids[2]);
        leftPointNode.setLeftChild(nodes.size());
        newTrapezoidNodes.push_back(nodes.size());
        nodes.push_back(leftTrapezoidNode);
    }

    if (!leftPointUnshared || newTrapezoids.size() == 4) {
        const Node rightTrapezoidNode(Node::TRAPEZOID, newTrapezoids.back());
        rightPointNode.setRightChild(nodes.size());
        newTrapezoidNodes.push_back(nodes.size());
        nodes.push_back(rightTrapezoidNode);
    }

    leftPointNode.setRightChild(nodes.size());
    nodes.push_back(rightPointNode);

    nodes[nodeToDelete] = leftPointNode;
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
