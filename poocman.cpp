#include "poocman.h"

Poocman::Poocman(TimerProxy *tpro, QString name, QGraphicsScene *parent) : AnimationSprite(tpro, name, parent)
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
}

Poocman::~Poocman() {

}

void Poocman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    // 45 pixel : could differ as the map changes
    painter -> drawPixmap(pos().x(), pos().y(), 45, 45,
                          *mSpriteImage,
                          mSubRect.x(), mSubRect.y(), mSubRect.width(), mSubRect.height());
    qDebug() << mSubRect;
}

QRectF Poocman::boundingRect() const {

}

