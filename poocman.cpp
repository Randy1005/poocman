#include "poocman.h"

Poocman::Poocman(TimerProxy *tpro, QString name) : AnimationSprite(tpro, name)
{
    // read anim descriptions (JSON file or any other format)
    QFile jsonfile;
    jsonfile.setFileName(name);
    jsonfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonParseError jsonError;
    QString val = jsonfile.readAll();
    chrJsonDoc = QJsonDocument::fromJson(val.toUtf8(), &jsonError);
    if (jsonError.error) {
        qDebug() << jsonError.errorString();
        return;
    }
    jsonfile.close();

    chrJsonObj = chrJsonDoc.object();

    // initialize mSpriteImage
    QString mSpritePath = ":/resource/" + chrJsonObj.value("sprite_name").toString();
    mSpriteImage = new QPixmap(mSpritePath);


    // this info belongs to "poocman.json"
    setSubRect(QRect(0, 0, mSpriteImage->width()/3, mSpriteImage->height()/4));


}

Poocman::~Poocman() {

}

void Poocman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 45 pixel : could differ as the map changes
    painter -> drawPixmap(pos().x(), pos().y(), 45, 45,
                          *mSpriteImage,
                          mSubRect.x(), mSubRect.y(), mSubRect.width(), mSubRect.height());
}

QRectF Poocman::boundingRect() const {

}
