#include "clyde.h"

Clyde::Clyde(TimerProxy *tpro, QString name, QGraphicsScene *sc, Maze *mzWidget) :
    Ghost(tpro, name, sc, mzWidget)
{
    setSpriteColor(QColor("orange"));

    setPos((offset+cell_unit)/2, cell_unit/2);

    availableDirs = std::vector<int>(0);


    setDirection(QPoint(-1, 0));
}

void Clyde::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget) {
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
    int safeDist = 4;

    // bump into a wall -> setSpeed(0)
    if ((getDirection() == QPoint(1, 0) && qRed(mazeWidget->getPixelRGB(centerX+bound, centerY)) != 0) ||
        (getDirection() == QPoint(-1, 0) && qRed(mazeWidget->getPixelRGB(centerX-bound-safeDist, centerY)) != 0) ||
        (getDirection() == QPoint(0, -1) && qRed(mazeWidget->getPixelRGB(centerX, centerY-bound-safeDist)) != 0) ||
        (getDirection() == QPoint(0, 1) && qRed(mazeWidget->getPixelRGB(centerX, centerY+bound)) != 0)) {
        setSpeed(0.0);
    }


    // determine which way to go
    std::mt19937 generator(rd());

    if (getSpeed() == 0.0) {
        // check clyde's current available directions (with his sensors[like a self-driving car])
        if (-getDirection() != QPoint(1, 0) && qRed(mazeWidget->getPixelRGB(centerX+bound, centerY)) == 0) {availableDirs.push_back(2);}
        if (-getDirection() != QPoint(-1, 0) && qRed(mazeWidget->getPixelRGB(centerX-bound-safeDist, centerY)) == 0) {availableDirs.push_back(3);}
        if (-getDirection() != QPoint(0, -1) && qRed(mazeWidget->getPixelRGB(centerX, centerY-bound-safeDist)) == 0) {availableDirs.push_back(0);}
        if (-getDirection() != QPoint(0, 1) && qRed(mazeWidget->getPixelRGB(centerX, centerY+bound)) == 0) {availableDirs.push_back(1);}

        // random index
        std::uniform_int_distribution<int> dis(0, availableDirs.size()-1);
        int rndIdx = dis(generator);

        setDirection(directions[availableDirs[rndIdx]]);

        availableDirs.clear();

        setSpeed(0.01);
    }


    // move clyde
    setPos(pos().x()+getDirection().x()*speed,
           pos().y()+getDirection().y()*speed);

    if (getDirection() == QPoint(0, -1)) {startAnim("move_up");}
    if (getDirection() == QPoint(0, 1)) {startAnim("move_down");}
    if (getDirection() == QPoint(1, 0)) {startAnim("move_right");}
    if (getDirection() == QPoint(-1, 0)) {startAnim("move_left");}
}

