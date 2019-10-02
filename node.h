#ifndef NODE_H
#define NODE_H
#include <QPoint>


class Node
{
public:
    Node(Node *, QPointF);

    int f, g, h;
    QPointF position;
    Node *parent;

    bool operator==(const Node &);

};

#endif // NODE_H
