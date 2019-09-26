#include "clyde.h"

Clyde::Clyde(TimerProxy *tpro, QString name, QGraphicsScene *sc, Maze *mzWidget) :
    Ghost(tpro, name, sc, mzWidget)
{
    setSpriteColor(QColor("orange"));

    seed = std::chrono::system_clock::now().time_since_epoch().count();
}

void Clyde::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget) {
    painter -> drawPixmap(pos().x(), pos().y(), cell_unit, cell_unit,
                          *mSpriteImage,
                          mSubRect.x(), mSubRect.y(), mSubRect.width(), mSubRect.height());


    // wall check (with RGB difference, the ghosts are only allowed to move along the black tiles, RGB=[0, 0, 0])
    // caution: we divided item coordinate by 2 before
    // so the pixmap coordinate has to be multiplied by 2 here
    int bound = (boundingRect().width()/(1.3));
    int centerX = pos().x()*2+bound;
    int centerY = pos().y()*2+bound;

    // check clyde's current available directions (with his sensors[like a self-driving car])
    if (qRed(mazeWidget->getPixelRGB(centerX+bound, centerY)) == 0) {availableDirs.push_back(2); currDir = 2;}
    if (qRed(mazeWidget->getPixelRGB(centerX-bound, centerY)) == 0) {availableDirs.push_back(3); currDir = 3;}
    if (qRed(mazeWidget->getPixelRGB(centerX, centerY-bound)) == 0) {availableDirs.push_back(0); currDir = 0;}
    if (qRed(mazeWidget->getPixelRGB(centerX, centerY+bound)) == 0) {availableDirs.push_back(1); currDir = 1;}


    // clyde's pattern is random but based on what his current choices are:
    if (availableDirs.size() == 1) {
        /*one direction available*/
        setDirection(directions[0]);
    } else if (availableDirs.size() == 2) {
        /*2 directions available*/
        if(std::find(availableDirs.begin(), availableDirs.end(), currDir) != availableDirs.end()) {
            /* availableDirs contains current direction */
            // keep going
        } else {
            shuffle(availableDirs.begin(), availableDirs.end(), std::default_random_engine(seed));
            setDirection(directions[availableDirs[0]]);
        }
    } else {
        /*3 or 4 directions available*/
        shuffle(availableDirs.begin(), availableDirs.end(), std::default_random_engine(seed));
        setDirection(directions[availableDirs[0]]);
    }

    // reset available directions
    availableDirs.clear();
}
