#include "gamescene.h"

GameScene::GameScene(QGraphicsView *v) : view(v)
{
    proxyItem = new QGraphicsProxyWidget();
    pacdots = new QList<Pacdot *>();
    scoreLabel = new QLabel();
    cntDownLabel = new QLabel();
    livesLabel = new QLabel();

    scoreLabel->setText(QString("score = %1").arg(Poocman::dotsEaten));
    scoreLabel->setGeometry(0, 0, 80, 20);
    scoreLabel->setStyleSheet("QLabel { background-color: none; color: black; font: bold large \"Courier New\"; font-size: 8pt}");
    cntDownLabel->setText(QString("time = %1").arg(TimerProxy::countdown));
    cntDownLabel->setGeometry(0, 20, 80, 20);
    cntDownLabel->setStyleSheet("QLabel { background-color: none; color: black; font: bold large \"Courier New\"; font-size: 8pt}");

    livesLabel->setText(QString("lives left = %1").arg(Poocman::lives));
    livesLabel->setGeometry(0, 40, 80, 20);
    livesLabel->setStyleSheet("QLabel { background-color: none; color: black; font: bold large \"Courier New\"; font-size: 7pt}");


    // initialize map [could be done in a smarter/customized way]
    // create a 9 x 9 maze map  (try 15x15 next time)
    map = {
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
    mz = new Maze();

    // new maze generator
    mGen = new MazeGenerator(map);

    // generate maze by backtracking
    mGen->carve_passages_from(1, 1, map);


    // setup map for maze
    mz->setVec(map);

    // create image pixmap of maze (for wall checking)
    mz->renderToPixmap();


    // game scene
    tpro = new TimerProxy();
    pc = new Poocman(tpro, ":/resource/poocman.json", this, mz);
    c = new Clyde(tpro, ":/resource/ghost.json", this, mz);
    c2 = new Clyde(tpro, ":/resource/ghost.json", this, mz);
    // Blinky *b = new Blinky(tpro, ":/resource/ghost.json", this, mz, pc);

    c->setSpeed(0.04);

    c2->setSpeed(0.1);
    c2->setSpriteColor(QColor("red"));
    c2->setPos((c2->offset+c2->cell_unit*(2*MAZE_PASSAGE_SIZE-1))/2, c2->cell_unit/2);

    setSceneRect(0, 0, mz->width(), mz->height());
    proxyItem = addWidget(mz);

    // place pacdots
    for (int i = 0; i < mz->width(); i+=15) {
        for (int j = 0; j < mz->height(); j+=15) {
            if (qRed(mz->getPixelRGB(i, j)) == 0) {
                Pacdot *pd = new Pacdot();
                pd->setPos(i/2, j/2);
                pacdots->push_back(pd);
                addItem(pd);
            }
        }
    }

    // focusable poocman item
    pc->setFlag(QGraphicsItem::ItemIsFocusable);
    pc->setFocus();


    addItem(pc);
    addItem(c);
    addItem(c2);
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
//    reset();
    view->setScene(new GameOverScene(view));
}

void GameScene::reset() {

    removeItem(pc);
    removeItem(c);
    removeItem(mz->graphicsProxyWidget());

    map = {
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


    mz = new Maze();
    mGen = new MazeGenerator(map);

    // generate maze by backtracking
    mGen->carve_passages_from(1, 1, map);

    // setup map for maze
    mz->setVec(map);

    // create image pixmap of maze (for wall checking)
    mz->renderToPixmap();

    proxyItem = addWidget(mz);

    // place pacdots
    for (int i = 0; i < mz->width(); i+=15) {
        for (int j = 0; j < mz->height(); j+=15) {
            if (qRed(mz->getPixelRGB(i, j)) == 0) {
                Pacdot *pd = new Pacdot();
                pd->setPos(i/2, j/2);
                pacdots->push_back(pd);
                addItem(pd);
            }
        }
    }

    pc = new Poocman(tpro, ":/resource/poocman.json", this, mz);
    c = new Clyde(tpro, ":/resource/ghost.json", this, mz);



    addItem(pc);
    addItem(c);
    c->setSpeed(0.04);


    // focusable poocman item
    pc->setFlag(QGraphicsItem::ItemIsFocusable);
    pc->setFocus();

}
