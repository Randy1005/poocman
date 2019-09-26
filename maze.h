#ifndef MAZE_H
#define MAZE_H

#include <QWidget>

class Maze : public QWidget
{
    Q_OBJECT

public:
    Maze(QWidget *parent = nullptr);
    ~Maze() override;
    void paintEvent(QPaintEvent *event = nullptr) override;
    void setVec(QList<QList<bool>> const &vec);
    void mousePressEvent(QMouseEvent *event) override;
    void renderToPixmap();
    QRgb getPixelRGB(int, int);

    QList<QList<bool>> vec_;
    QPixmap *mazePixmap;
    QPixmap pixmap_scaled;
};

#endif // MAZE_H
