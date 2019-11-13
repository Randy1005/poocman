#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

class Button : public QGraphicsItem
{
public:
    Button(QString, QString);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QString spritePath;
    QImage img;
    QString text;
};

#endif // BUTTON_H
