#include "menuscene.h"

MenuScene::MenuScene(QGraphicsView *view)
{
    setSceneRect(0, 0, 640, 480);
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    logo = new Button(":/resource/logo.png", "", view);
    logo->setPos(100, 50);
    logo->setScale(0.32);

    startButton = new Button(":/resource/button_sprite.png", "PLAY", view);
    startButton->setScale(0.5);
    startButton->setPos(150, 150);

    instrButton = new Button(":/resource/button_sprite.png", "HELP", view);
    instrButton->setScale(0.5);
    instrButton->setPos(150, 205);


    exitButton = new Button(":/resource/button_sprite.png", "EXIT", view);
    exitButton->setScale(0.5);
    exitButton->setPos(150, 260);

    addItem(logo);
    addItem(startButton);
    addItem(instrButton);
    addItem(exitButton);
}
