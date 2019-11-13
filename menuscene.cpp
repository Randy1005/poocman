#include "menuscene.h"

MenuScene::MenuScene()
{
    setSceneRect(0, 0, 640, 480);

    logo = new Button(":/resource/logo.png", "");
    logo->setPos(100, 50);
    logo->setScale(0.32);

    startButton = new Button(":/resource/button_sprite.png", "PLAY");
    startButton->setScale(0.5);
    startButton->setPos(150, 150);

    instrButton = new Button(":/resource/button_sprite.png", "HELP");
    instrButton->setScale(0.5);
    instrButton->setPos(150, 205);


    exitButton = new Button(":/resource/button_sprite.png", "EXIT");
    exitButton->setScale(0.5);
    exitButton->setPos(150, 260);

    addItem(logo);
    addItem(startButton);
    addItem(instrButton);
    addItem(exitButton);
}
