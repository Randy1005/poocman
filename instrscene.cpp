#include "instrscene.h"

InstrScene::InstrScene(QGraphicsView *v) : view(v)
{

    setSceneRect(0, 0, 640, 480);
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    instructions = new QLabel();
    instructions->setStyleSheet("QLabel { background-color: black; color: white; font: bold large \"Courier New\"; font-size: 16pt}");
    instructions->setText(QString("Arrow Keys to move\nWatch out for ghosts!"));
    instructions->setGeometry(200, 180, 400, 100);


    returnButton = new Button(":/resource/button_sprite.png", "BACK", view);
    returnButton->setScale(0.5);
    returnButton->setPos(150, 200);

    addWidget(instructions);
    addItem(returnButton);
}
