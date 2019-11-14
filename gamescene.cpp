#include "gamescene.h"

GameScene::GameScene(QGraphicsView *v) : view(v)
{


    scoreLabel = new QLabel();
    cntDownLabel = new QLabel();
    livesLabel = new QLabel();

    scoreLabel->setText(QString("score = %1").arg(Poocman::dotsEaten));
    scoreLabel->setGeometry(0, 0, 80, 20);
    scoreLabel->setStyleSheet("QLabel { background-color: none; color: black; font: bold large \"Courier New\"; font-size: 8pt}");
    cntDownLabel->setText(QString("time = %1").arg(TimerProxy::countdown));
    cntDownLabel->setGeometry(0, 20, 80, 20);
    cntDownLabel->setStyleSheet("QLabel { background-color: none; color: black; font: bold large \"Courier New\"; font-size: 8pt}");

    livesLabel->setText(QString("lives left = %1").arg(3));
    livesLabel->setGeometry(0, 40, 80, 20);
    livesLabel->setStyleSheet("QLabel { background-color: none; color: black; font: bold large \"Courier New\"; font-size: 7pt}");


    // initialize map [could be done in a smarter/customized way]
    // create a 9 x 9 maze map  (try 15x15 next time)
    QList<QList<bool>> map {
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false},
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}
    };


    // new maze widget
    Maze *mz = new Maze();

    // new maze generator
    MazeGenerator *mGen = new MazeGenerator(map);

    // generate maze by backtracking
    mGen->carve_passages_from(1, 1, map);


    // setup map for maze
    mz->setVec(map);

    // create image pixmap of maze (for wall checking)
    mz->renderToPixmap();


    // game scene
    TimerProxy *tpro = new TimerProxy();
    Poocman *pc = new Poocman(tpro, ":/resource/poocman.json", this, mz);
    Clyde *c = new Clyde(tpro, ":/resource/ghost.json", this, mz);
//    Blinky *b = new Blinky(tpro, ":/resource/ghost.json", this, mz, pc);

    c->setSpeed(0.01);

    setSceneRect(0, 0, mz->width(), mz->height());
    addWidget(mz);

    // place pacdots
    for (int i = 0; i < mz->width(); i+=15) {
        for (int j = 0; j < mz->height(); j+=15) {
            if (qRed(mz->getPixelRGB(i, j)) == 0) {
                Pacdot *pd = new Pacdot();
                pd->setPos(i/2, j/2);
                addItem(pd);
            }
        }
    }

    // focusable poocman item
    pc->setFlag(QGraphicsItem::ItemIsFocusable);
    pc->setFocus();


    addItem(pc);
    addItem(c);
    addWidget(scoreLabel);
    addWidget(cntDownLabel);
    addWidget(livesLabel);

    // connect signals and slots
    QObject::connect(pc, SIGNAL(gamesceneUpdateInfo(QString)),
                         this, SLOT(updateLabel(QString)));
    QObject::connect(tpro, SIGNAL(gamesceneUpdateInfo(QString)),
                         this, SLOT(updateLabel(QString)));

    QObject::connect(pc, SIGNAL(changeScene()),
                         this, SLOT(switchScene()));
    QObject::connect(tpro, SIGNAL(changeScene()),
                         this, SLOT(switchScene()));

}

void GameScene::updateLabel(QString name) {
    if (name == "score") {
        scoreLabel->setText(QString("score = %1").arg(Poocman::dotsEaten));
    } else if (name == "cntDown") {
        cntDownLabel->setText(QString("time = %1").arg(TimerProxy::countdown));
    } else if (name == "lives") {
        livesLabel->setText(QString("lives left = %1").arg(Poocman::lives));
    }
}

void GameScene::switchScene() {
    view->setScene(new GameOverScene(view));
}
