#include "poocman.h"

Poocman::Poocman(TimerProxy *tpro, QString name, QGraphicsScene *parent, Maze *mzWidget) :
    AnimationSprite(tpro, name, parent, mzWidget)
{
    // read animation descriptions (JSON file or any other format)
    QFile jsonfile;
    jsonfile.setFileName(name);
    jsonfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonParseError jsonError;
    QString val = jsonfile.readAll();
    chrJsonDoc = QJsonDocument::fromJson(val.toUtf8(), &jsonError);
    if (jsonError.error) {
        qWarning() << jsonError.errorString();
        return;
    }
    jsonfile.close();

    chrJsonObj = chrJsonDoc.object();

    // initialize mSpriteImage
    QString mSpritePath = ":/resource/" + chrJsonObj.value("sprite_name").toString();
    mSpriteImage = new QPixmap(mSpritePath);

    // initialize animation
    startAnim("idle");

    // initialize speed/direction
    setDirection({0, 0});

    // set initial position (scenePos / 2) [just some random conversion, don't really know why]
    setPos((offset+cell_unit)/2, cell_unit/2);
    // -- calling mapToScene in this case does not work, cuz the item has not yet been added to the scene -- //
}

Poocman::~Poocman() {
}

void Poocman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter -> drawPixmap(pos().x(), pos().y(), cell_unit, cell_unit,
                          *mSpriteImage,
                          mSubRect.x(), mSubRect.y(), mSubRect.width(), mSubRect.height());


    // wall check (with RGB difference, poocman is only allowed to move along the black tiles, RGB=[0, 0, 0])
    // caution: we divided item coordinate by 2 before
    // so the pixmap coordinate has to be multiplied by 2 here
    int bound = boundingRect().height()/2;
    int centerX = (pos().x()+bound)*2;
    int centerY = (pos().y()+bound)*2;
    int safeDist = 5;
    if ((currDir == 2 && qRed(mazeWidget->getPixelRGB(centerX+bound, centerY)) == 0) ||
        (currDir == 3 && qRed(mazeWidget->getPixelRGB(centerX-bound-safeDist, centerY)) == 0) ||
        (currDir == 0 && qRed(mazeWidget->getPixelRGB(centerX, centerY-bound-safeDist)) == 0) ||
        (currDir == 1 && qRed(mazeWidget->getPixelRGB(centerX, centerY+bound)) == 0)) {
        setSpeed(0.02);
        setPos(pos().x()+direction.x()*speed,
               pos().y()+direction.y()*speed);
    }

    // collision with pacdots
    QList<QGraphicsItem *> collItems = this->collidingItems();
    foreach(QGraphicsItem *itm, collItems) {
        Pacdot *dot = dynamic_cast<Pacdot *>(itm);
        if (dot) scene->removeItem(dot);
    }


}

QRectF Poocman::boundingRect() const {
    return mSubRect;
}

void Poocman::setSpeed(double newSpeed) {
    speed = newSpeed;
}

double Poocman::getSpeed() {
    return speed;
}

void Poocman::setDirection(QPoint dir) {
    direction = dir;
}

QPoint Poocman::getDirection() {
    return direction;
}

void Poocman::keyPressEvent(QKeyEvent *event) {

    switch(event->key()) {
    case Qt::Key_Up:
        setDirection({0, -1});
        currDir = 0;
        startAnim("move_up");
        break;
    case Qt::Key_Down:
        setDirection({0, 1});
        currDir = 1;
        startAnim("move_down");
        break;
    case Qt::Key_Right:
        setDirection({1, 0});
        currDir = 2;
        startAnim("move_right");
        break;
    case Qt::Key_Left:
        setDirection({-1, 0});
        currDir = 3;
        startAnim("move_left");
        break;
    }
}


