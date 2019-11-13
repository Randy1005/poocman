#include "button.h"

Button::Button(QString path, QString text) : spritePath(path), text(text)
{
    img = QImage(path);
}

QRectF Button::boundingRect() const {
    return QRectF(scenePos().x(), scenePos().y(), img.width(), img.height());
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawImage(QRectF(scenePos().x(), scenePos().y(), img.width(), img.height()), img, img.rect(), Qt::AutoColor);
    painter->setFont(QFont("Courier New", 36, QFont::Bold));
    painter->drawText(QPointF(scenePos().x()+boundingRect().width()/2, scenePos().y()+boundingRect().height()/2), text);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << this->text;
        if (this->text == "PLAY") {

        } else if (this->text == "HELP") {

        } else if (this->text == "EXIT") {

        }
    }

}
