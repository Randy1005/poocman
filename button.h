#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QCoreApplication>
#include "poocman.h"
#include "timerproxy.h"


class Button : public QGraphicsItem
{
public:
    Button(QString, QString, QGraphicsView *);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QString spritePath;
    QImage img;
    QString text;
    QGraphicsView *view;

    static QGraphicsScene *menu, *game, *gameover, *instr;

};

#endif // BUTTON_H
