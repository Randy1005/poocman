#include "node.h"

Node::Node(Node *parentNode, QPointF pos) :
    position(pos), parent(parentNode)
{

}

bool Node::operator==(const Node &other) {
    return (position == other.position);
}
