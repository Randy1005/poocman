#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <QGraphicsScene>
#include "button.h"


class MenuScene : public QGraphicsScene
{
public:
    MenuScene();
    Button *logo;
    Button *startButton;
    Button *instrButton;
    Button *exitButton;

};

#endif // MENUSCENE_H
