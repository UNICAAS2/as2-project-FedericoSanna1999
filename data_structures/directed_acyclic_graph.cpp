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

    // the left child of the segment node is the upper trapezoid node
    segmentNode.setLeftChild(nodes.size());
    newTrapezoidNodes.push_back(nodes.size());
    nodes.push_back(upperTrapezoidNode);

    // the right child of the segment node is the lower trapezoid node
    segmentNode.setRightChild(nodes.size());
    newTrapezoidNodes.push_back(nodes.size());
    nodes.push_back(lowerTrapezoidNode);

    Node rightPointNode(Node::POINT, rightPoint);

    // the left child of the right point node is the segment node
    rightPointNode.setLeftChild(nodes.size());
    nodes.push_back(segmentNode);

    Node leftPointNode(Node::POINT, leftPoint);

    // if the left point of the segment is a new point
    if (leftPointUnshared) {
        const Node leftTrapezoidNode(Node::TRAPEZOID, newTrapezoids[2]);

        // the left child of the left point node is the left trapezoid node
        leftPointNode.setLeftChild(nodes.size());
        newTrapezoidNodes.push_back(nodes.size());
        nodes.push_back(leftTrapezoidNode);
    }

    // if the right point of the segment is a new point
    if (!leftPointUnshared || newTrapezoids.size() == 4) {
        const Node rightTrapezoidNode(Node::TRAPEZOID, newTrapezoids.back());

        // the right child of the right point node is the right trapezoid node
        rightPointNode.setRightChild(nodes.size());
        newTrapezoidNodes.push_back(nodes.size());
        nodes.push_back(rightTrapezoidNode);
    }

    // the right child of the left point nod is the right point node
    leftPointNode.setRightChild(nodes.size());
    nodes.push_back(rightPointNode);

    // the node of the trapezoid to be deleted is update with the node of the left point
    nodes[nodeToDelete] = leftPointNode;
}

/**
 * @brief DirectedAcyclicGraph::update allows the directed acyclic graph to be updated when a segment intersects more trapezoids.
 * @param nodesToDelete is the vector which contains the node of the trapezoids intersected by the segment.
 * @param leftPoint is the left point of the segment which intersects the trapezoids (it is null if the point already exists).
 * @param rightPoint is the right point of the segment which intersects the trapezoids (it is null if the point already exists).
 * @param segment is the index of the segment which intersects the trapezoids.
 * @param newTrapezoids is the vector which contains the new trapezoids indexes.
 * @param newTrapezoidNodes is the vector which contains the indexes of the new trapezoid nodes.
 * @param leftChildren is the vector which contains the indexes of the node to delete which are above of the segment, so the left children of the new segment nodes.
 * @param rightChildren is the vector which contains the indexes of the node to delete which are below of the segment, so the right children of the new segment nodes.
 */
void DirectedAcyclicGraph::update(std::vector<size_t>& nodesToDelete, const size_t& leftPoint, const size_t& rightPoint, const size_t& segment, const std::vector<size_t>& newTrapezoids, std::vector<size_t>& newTrapezoidNodes, std::vector<size_t>& leftChildren, std::vector<size_t>& rightChildren) {
    // if the first intersected trapezoid contains the left point of the segment
    if (leftPoint != std::numeric_limits<size_t>::max()) {
        // the node of the first intersected trapezoid becomes a point node
        nodes[nodesToDelete.front()].setType(Node::POINT);

        // create the trapezoid node to the left of the left point
        const Node leftTrapezoidNode(Node::TRAPEZOID, newTrapezoids.front());

        // the left trapezoid node becomes the left child of the left point node
        nodes[nodesToDelete.front()].setLeftChild(nodes.size());
        newTrapezoidNodes.push_back(nodes.size());
        nodes.push_back(leftTrapezoidNode);

        // create the trapezoid node to the right of the left point
        const Node rightTrapezoidNode(Node::TRAPEZOID, nodes[nodesToDelete.front()].getObject());

        // update the object of the left point node
        nodes[nodesToDelete.front()].setObject(leftPoint);

        // the right trapezoid node becomes the right child of the left point node
        nodes[nodesToDelete.front()].setRightChild(nodes.size());

        // update the index of the first node to delete with the index of the right trapezoid node.
        if (leftChildren.front() == nodesToDelete.front())
            leftChildren[0] = nodes.size();
        else
            rightChildren[0] = nodes.size();

        nodesToDelete[0] = nodes.size();
        nodes.push_back(rightTrapezoidNode);
    }

    // if the last intersected trapezoid contains the right point of the segment
    if (rightPoint != std::numeric_limits<size_t>::max()) {
        // the node of the last intersected trapezoid becomes a point node
        nodes[nodesToDelete.back()].setType(Node::POINT);

        // create the trapezoid node to the right of the right point
        const Node rightTrapezoidNode(Node::TRAPEZOID, (newTrapezoids.size() == 3) ? newTrapezoids[1] : newTrapezoids[0]);

        // the right trapezoid node becomes the right child of the right point node
        nodes[nodesToDelete.back()].setRightChild(nodes.size());
        newTrapezoidNodes.push_back(nodes.size());
        nodes.push_back(rightTrapezoidNode);

        // create the trapezoid node to the left of the right point
        const Node leftTrapezoidNode(Node::TRAPEZOID, nodes[nodesToDelete.back()].getObject());

        // update the object of the right point node
        nodes[nodesToDelete.back()].setObject(rightPoint);

        // the left trapezoid node becomes the left child of the right point node
        nodes[nodesToDelete.back()].setLeftChild(nodes.size());

        // update the index of the last node to delete with the index of the left trapezoid node
        if (leftChildren.back() == nodesToDelete.back())
            leftChildren[leftChildren.size() - 1] = nodes.size();
        else
            rightChildren[rightChildren.size() - 1] = nodes.size();

        nodesToDelete[nodesToDelete.size() - 1] = nodes.size();
        nodes.push_back(leftTrapezoidNode);
    }

    std::vector<size_t>::iterator leftChild = leftChildren.begin();
    std::vector<size_t>::iterator rightChild = rightChildren.begin();

    for (size_t i = 0; i < nodesToDelete.size(); i++) {
        // the node to delete becomes a segment node
        nodes[nodesToDelete[i]].setType(Node::SEGMENT);

        // update the node index in the vector "leftChildren" with the new one which stores the old trapezoid
        while (leftChild != leftChildren.end() && *leftChild == nodesToDelete[i]) {
            *leftChild = nodes.size();
            leftChild++;
        }

        // update the node index in the vector "rightChildren" with the new one which stores the old trapezoid
        while (rightChild != rightChildren.end() && *rightChild == nodesToDelete[i]) {
            *rightChild = nodes.size();
            rightChild++;
        }

        // store the new trapezoid node index
        newTrapezoidNodes.push_back(nodes.size());

        // create the new trapezoid node with the trapezoid stored in the node to delete
        nodes.push_back(Node(Node::TRAPEZOID, nodes[nodesToDelete[i]].getObject()));

        // update the object of the segment node
        nodes[nodesToDelete[i]].setObject(segment);
    }

    // update the node index in the vector "leftChildren" with the new one which stores the new trapezoid
    while (leftChild != leftChildren.end() && *leftChild == std::numeric_limits<size_t>::max()) {
        *leftChild = nodes.size();
        leftChild++;
    }

    // update the node index in the vector "rightChildren" with the new one which stores the new trapezoid
    while (rightChild != rightChildren.end() && *rightChild == std::numeric_limits<size_t>::max()) {
        *rightChild = nodes.size();
        rightChild++;
    }

    // store the new trapezoid node index
    newTrapezoidNodes.push_back(nodes.size());

    // create the new trapezoid node with the new trapezoid
    nodes.push_back(Node(Node::TRAPEZOID, newTrapezoids.back()));

    // update the left and the right children of the node to delete which is a segment node
    for (size_t i = 0; i < nodesToDelete.size(); i++) {
        nodes[nodesToDelete[i]].setLeftChild(leftChildren[i]);
        nodes[nodesToDelete[i]].setRightChild(rightChildren[i]);
    }
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
