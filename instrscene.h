#ifndef INSTRSCENE_H
#define INSTRSCENE_H
#include <QGraphicsScene>
#include <QLabel>
#include "button.h"

class InstrScene : public QGraphicsScene
{
public:
    InstrScene(QGraphicsView *);
    QGraphicsView *view;
    QLabel *instructions;
    Button *returnButton;


};

#endif // INSTRSCENE_H
