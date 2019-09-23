#include "poocman.h"

Poocman::Poocman(TimerProxy *tpro, QString name, QGraphicsScene *parent, QList<QList<bool>> map) : AnimationSprite(tpro, name, parent, map)
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
    setSpeed(0.005);
    setDirection({0, 0});

    setPos(offset+cell_unit, cell_unit);

}

Poocman::~Poocman() {

}

void Poocman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter -> drawPixmap(pos().x(), pos().y(), cell_unit*2, cell_unit*2,
                          *mSpriteImage,
                          mSubRect.x(), mSubRect.y(), mSubRect.width(), mSubRect.height());



    for (int i = 0; i < 2*MAZE_PASSAGE_SIZE+1; i++) {
        for (int j = 0; j < 2*MAZE_PASSAGE_SIZE+1; j++) {
            if (gameMap[i][j] == false &&
                pos().x() > gridtogameCoord({i, j}).x() && pos().x() < (gridtogameCoord({i, j}).x()+cell_unit) &&
                pos().y() > gridtogameCoord({i, j}).y() && pos().y() < (gridtogameCoord({i, j}).y()+cell_unit)) {
                setSpeed(0);
            }
        }
    }

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
        startAnim("move_up");
        break;
    case Qt::Key_Down:
        setDirection({0, 1});
        startAnim("move_down");
        break;
    case Qt::Key_Right:
        setDirection({1, 0});
        startAnim("move_right");
        break;
    case Qt::Key_Left:
        setDirection({-1, 0});
        startAnim("move_left");
        break;
    }
}

