#ifndef MAZE_H
#define MAZE_H

#include <QWidget>

class Maze : public QWidget
{
    Q_OBJECT

public:
    Maze(QWidget *parent = 0);
    ~Maze();
    void paintEvent(QPaintEvent *event = 0);
    void setVec(QList<QList<bool>> const &vec);

    QList<QList<bool>> vec_;
};

#endif // MAZE_H
