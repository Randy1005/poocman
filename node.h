#ifndef NODE_H
#define NODE_H
#include <QPoint>


class Node
{
public:
    Node(Node *, QPoint);

    int f, g, h;
    QPoint position;
    Node *parent;

    bool operator==(const Node &);

};

#endif // NODE_H
