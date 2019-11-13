#include "gamescene.h"

GameScene::GameScene()
{
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

}
