#ifndef PACDOT_H
#define PACDOT_H

#include <QGraphicsObject>
#include <QPainter>
#include "commonInfo.h"


class Pacdot : public QGraphicsObject
{
public:
    Pacdot();
    ~Pacdot() override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;


private:
    QPixmap pixmap;
    QPixmap scaled;

};

#endif // PACDOT_H
