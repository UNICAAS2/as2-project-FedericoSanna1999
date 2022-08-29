#include "node.h"

/**
 * @brief Node::Node is the constructor of the class which allows a type and object to be assigned, while node children are null by default.
 * @param type is the type of the object being stored.
 * @param object is the index in the vector in which it is stored.
 */
Node::Node(const Type& type, const size_t& object) :
    type(type), object(object) {

}

/**
 * @brief Node::getType returns the type of the object being stored.
 * @return the type of the object being stored.
 */
Node::Type Node::getType() const {
    return type;
}

/**
 * @brief Node::getObject returns the index in the vector in which it is stored.
 * @return the index in the vector in which it is stored.
 */
size_t Node::getObject() const {
    return object;
}

/**
 * @brief Node::getLeftChild returns the index in the vector "nodes" in which it is stored or a specific value which represents null.
 * @return the index in the vector "nodes" in which it is stored or a specific value which represents null.
 */
size_t Node::getLeftChild() const {
    return leftChild;
}

/**
 * @brief Node::getRightChild returns the index in the vector "nodes" in which it is stored or a specific value which represents null.
 * @return the index in the vector "nodes" in which it is stored or a specific value which represents null.
 */
size_t Node::getRightChild() const {
    return rightChild;
}

/**
 * @brief Node::setType allows to assign a type.
 * @param type is the type of the object being stored.
 */
void Node::setType(const Type& type) {
    this->type = type;
}

/**
 * @brief Node::setObject allows to assign an object.
 * @param object is the index in the vector in which it is stored.
 */
void Node::setObject(const size_t& object) {
    this->object = object;
}

/**
 * @brief Node::setLeftChild allows to assign a left child.
 * @param leftChild is the index in the vector "nodes" in which it is stored or a specific value which represents null.
 */
void Node::setLeftChild(const size_t& leftChild) {
    this->leftChild = leftChild;
}

/**
 * @brief Node::setRightChild allows to assign a right child.
 * @param rightChild is the index in the vector "nodes" in which it is store or a specific value which represents null.
 */
void Node::setRightChild(const size_t& rightChild) {
    this->rightChild = rightChild;
}
