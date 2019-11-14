#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include <QGraphicsView>
#include <QLabel>
#include "button.h"
#include "poocman.h"


class GameOverScene : public QGraphicsScene
{
public:
    GameOverScene(QGraphicsView *);
    QGraphicsView *view;

    QLabel *finalScore;
    Button *logo;
    Button *menuButton;
    Button *exitButton;

};

#endif // GAMEOVERSCENE_H
