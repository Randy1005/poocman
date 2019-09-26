#include "ghost.h"

Ghost::Ghost(TimerProxy *tpro, QString name, QGraphicsScene *parent, Maze *mzWidget) :
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

    qDebug() << mSpritePath;

    // initialize animation
    startAnim("move_up");

    // initialize speed/direction
    setDirection({0, 0});

}

Ghost::~Ghost() {

}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

QRectF Ghost::boundingRect() const {
    return mSubRect;
}

void Ghost::setSpeed(double newSpeed) {
    speed = newSpeed;
}

double Ghost::getSpeed() {
    return speed;
}

void Ghost::setDirection(QPoint dir) {
    direction = dir;
}

QPoint Ghost::getDirection() {
    return direction;
}

void Ghost::setSpriteColor(QColor clr) {
    QImage img = mSpriteImage->toImage();
    for (int x = 0; x < mSpriteImage->width(); x++) {
        for (int y = 0; y < mSpriteImage->height(); y++) {
            if (!(qRed(img.pixel(x, y)) == qGreen(img.pixel(x, y)) == qBlue(img.pixel(x, y))) == 0) {
                    img.setPixel(x, y, clr.rgb());
            }
        }
    }

    mSpriteImage->convertFromImage(img);
}
