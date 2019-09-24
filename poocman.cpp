#include "poocman.h"

Poocman::Poocman(TimerProxy *tpro, QString name, QGraphicsScene *parent, QList<QList<bool>> map, Maze *mzWidget) : AnimationSprite(tpro, name, parent, map, mzWidget)
{
    // read anim descriptions (JSON file or any other format)
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

    // test animation
    startAnim("move_right");

    // initialize speed/direction/position
    setSpeed(0.01);
    setDirection({0, 0});

    // set initial position
    // ----- coordinate somehow not unified ----- //
    setPos(offset+cell_unit, cell_unit);


}

Poocman::~Poocman() {

}

void Poocman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter -> drawPixmap(pos().x(), pos().y(), cell_unit, cell_unit,
                          *mSpriteImage,
                          mSubRect.x(), mSubRect.y(), mSubRect.width(), mSubRect.height());


    // wall check (with RGB difference)
    int halfSize = (boundingRect().height()/2);
    int centerX = pos().x()+halfSize;
    int centerY = pos().y()+halfSize;

    if (currDir == 2) {
        if (qRed(mazeWidget->getPixelRGB(centerX+halfSize, centerY)) == 128) {
            // stop
            return;
        }

    } else if (currDir == 3) {
        if (qRed(mazeWidget->getPixelRGB(centerX-halfSize, centerY)) == 128) {
            return;
        }

    } else if (currDir == 0) {
        if (qRed(mazeWidget->getPixelRGB(centerX, centerY-halfSize)) == 128) {
            return;
        }

    } else if (currDir == 1) {
        if (qRed(mazeWidget->getPixelRGB(centerX, centerY+halfSize)) == 128) {
            return;
        }

    } else {

    }

    setSpeed(0.01);
    setPos(pos().x()+direction.x()*speed,
           pos().y()+direction.y()*speed);

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


