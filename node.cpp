#include "node.h"

Node::Node(Node *parentNode, QPoint pos) :
    position(pos), parent(parentNode)
{
    f = g = h = 0;

}

bool Node::operator==(const Node &other) {
    return (position == other.position);
}
