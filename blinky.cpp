#include "blinky.h"

Blinky::Blinky(TimerProxy *tpro, QString name, QGraphicsScene *sc, Maze *mzWidget, Poocman *pc) :
    Ghost(tpro, name, sc, mzWidget)
{
    setSpriteColor(QColor("red"));

    setPos((offset+cell_unit)/2, cell_unit/2);

    pcman = pc;

    for (int i = 0; i < newPositions.size(); i++) {
        newPositions[i] *= 5;
    }
}

void Blinky::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget) {
    painter -> drawPixmap(pos().x(), pos().y(), cell_unit, cell_unit,
                          *mSpriteImage,
                          mSubRect.x(), mSubRect.y(), mSubRect.width(), mSubRect.height());


    // wall check (with RGB difference, the ghosts are only allowed to move along the black tiles, RGB=[0, 0, 0])
    // caution: we divided item coordinate by 2 before
    // so the pixmap coordinate has to be multiplied by 2 here
    // sometimes "bound" needs to be adjusted, much like sensor sensitivity
    int bound = boundingRect().height()/2;
    int centerX = (pos().x()+bound)*2;
    int centerY = (pos().y()+bound)*2;
    int safeDist = 6;



    // move blinky
    setPos(pos().x()+getDirection().x()*speed,
           pos().y()+getDirection().y()*speed);

    if (getDirection() == QPoint(0, -1)) {startAnim("move_up");}
    if (getDirection() == QPoint(0, 1)) {startAnim("move_down");}
    if (getDirection() == QPoint(1, 0)) {startAnim("move_right");}
    if (getDirection() == QPoint(-1, 0)) {startAnim("move_left");}
}

QVector<Node *> Blinky::aStar(Maze *mz, Node *startNode, Node *endNode) {
    // initialize open and closed list
    QVector<Node *> openList, closedList;

    // append startNode to openList
    openList.append(startNode);

    // loop until we find the endNode
    while (openList.size() > 0) {
        // get the current node
        Node *currNode = openList.front();
        int currIdx = 0;
        for(int i = 0; i < openList.size(); i++) {
            if (openList[i]->f < currNode->f) {
                currNode = openList[i];
                currIdx = i;
            }
        }

        // pop currNode off open list, append to closed list
        openList.erase(openList.begin() + currIdx);
        closedList.append(currNode);

        // if we found the endNode
        if (*currNode == *endNode) {
            QVector<Node *> path;
            Node *curr = currNode;
            while (curr != nullptr) {
                path.append(curr);
                curr = curr->parent;
            }

            // reverse the path and return
            std::reverse(path.begin(), path.end());
            return path;
        }

        // generate children
        QVector<Node *> children;
        QPoint nodePos;
        for (int i = 0; i < newPositions.size(); i++) {
            nodePos = currNode->position + newPositions[i];

            // check if it's walkable
            if (qRed(mz->getPixelRGB(nodePos.x(), nodePos.y())) != 0)
                continue;

            // create new node and append to children list
            Node *newNode = new Node(currNode, nodePos);
            children.append(newNode);
        }

        // loop through children
        for (int i = 0; i < children.size(); i++) {
            // if child is in closedList
            for (int j = 0; j < closedList.size(); j++) {
                if (*children[i] == *closedList[j])
                    continue;
            }

            // store f, g, h
            children[i]->g = currNode->g + 1;
            children[i]->h = (children[i]->position.x()-endNode->position.x())*(children[i]->position.x()-endNode->position.x()) +
                             (children[i]->position.y()-endNode->position.y())*(children[i]->position.y()-endNode->position.y());
            children[i]->f = children[i]->g + children[i]->h;

            // if child is already in open list
            for (int k = 0; k < openList.size(); k++) {
                if (*children[i] == *openList[k] && children[i]->g > openList[k]->g)
                    continue;
            }

            // append to openList
            openList.append(children[i]);
        }

    }


}


