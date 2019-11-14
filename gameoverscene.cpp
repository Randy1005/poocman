#include "gameoverscene.h"

GameOverScene::GameOverScene(QGraphicsView *v) : view(v)
{
    setSceneRect(0, 0, 640, 480);
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    logo = new Button(":/resource/game_over.png", "", view);
    logo->setPos(115, 50);
    logo->setScale(0.8);

    finalScore = new QLabel();
    finalScore->setStyleSheet("QLabel { background-color: black; color: white; font: bold large \"Courier New\"; font-size: 16pt}");
    finalScore->setText(QString("score = %1").arg(Poocman::dotsEaten));
    finalScore->setGeometry(260, 180, 150, 20);


    menuButton = new Button(":/resource/button_sprite.png", "MENU", view);
    menuButton->setScale(0.5);
    menuButton->setPos(150, 150);

    exitButton = new Button(":/resource/button_sprite.png", "EXIT", view);
    exitButton->setScale(0.5);
    exitButton->setPos(150, 205);

    addItem(menuButton);
    addItem(exitButton);
    addItem(logo);
    addWidget(finalScore);

}
