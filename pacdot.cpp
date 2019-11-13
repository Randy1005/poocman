#include "pacdot.h"

Pacdot::Pacdot()
{
    pixmap = QPixmap(":/resource/pacdot.png");
    pixmap = pixmap.scaled(6, 6, Qt::KeepAspectRatio);
}

Pacdot::~Pacdot() {

}

void Pacdot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(pos(), pixmap);
}

QRectF Pacdot::boundingRect() const {
    return QRectF(scenePos().x(), scenePos().y(), 6, 6);
}
