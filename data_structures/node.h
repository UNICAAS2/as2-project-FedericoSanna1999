#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <limits>

/**
 * @brief The Node class allows to create nodes which can store:
 * - an object as an index in a vector in which it is stored such as "points", "segments", "trapezoids";
 * - an object type such as "POINT", "SEGMENT", "TRAPEZOID";
 * - a leftChild and a rightChild as indexes in the vector "nodes" in which they are stored.
 * std::numeric_limits<size_t>::max() represents null.
 */
class Node {

public:
    typedef enum {POINT, SEGMENT, TRAPEZOID} Type;

    Node(const Type& type, const size_t& object);

    Type getType() const;
    size_t getObject() const;

    size_t getLeftChild() const;
    size_t getRightChild() const;

    void setType(const Type& type);
    void setObject(const size_t& object);

    void setLeftChild(const size_t& leftChild);
    void setRightChild(const size_t& rightChild);

private:
    Type type;
    size_t object;

    size_t leftChild = std::numeric_limits<size_t>::max();
    size_t rightChild = std::numeric_limits<size_t>::max();

};

#endif // NODE_H
