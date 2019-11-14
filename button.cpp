#include "button.h"

Button::Button(QString path, QString text, QGraphicsView *v) : spritePath(path), text(text), view(v)
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
            view->setScene(game);
            Poocman::lives = 3;
            Poocman::dotsEaten = 0;
            TimerProxy::countdown = 5;
        } else if (this->text == "HELP") {
            view->setScene(instr);
        } else if (this->text == "EXIT") {
            QCoreApplication::quit();
        } else if (this->text == "BACK" || this->text == "MENU") {
            view->setScene(menu);
        }
    }

}
