#include "blinky.h"

Blinky::Blinky(TimerProxy *tpro, QString name, QGraphicsScene *sc, Maze *mzWidget, Poocman *pc) :
    Ghost(tpro, name, sc, mzWidget)
{
    setSpriteColor(QColor("red"));

    setPos((offset+cell_unit)/2, cell_unit/2);

    pcman = pc;
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
