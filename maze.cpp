#include <QtGui>
#include <QtCore>

#include "maze.h"


Maze::Maze(QWidget *parent) : QWidget(parent) {

}

Maze::~Maze() {

}

void Maze::paintEvent(QPaintEvent *event) {
    QPixmap pixmap(vec_.front().size(), vec_.size());
    QPainter pixmap_painter(&pixmap);

    for(int y = 0; y < vec_.size(); y++) {
        for(int x = 0; x < vec_[y].size(); x++) {
            pixmap_painter.setPen(vec_[y][x] ? QColor("black") : QColor("darkblue"));
            pixmap_painter.drawPoint(x, y); // Draw individual pixels
        }
    }

    QPainter painter(this);
    QPixmap pixmap_scaled = pixmap.scaled(size(), Qt::KeepAspectRatio); // scale to fit the widget

    painter.drawPixmap(
        (width() - pixmap_scaled.width()) / 2,
        (height() - pixmap_scaled.height()) / 2,
        pixmap_scaled.width(), pixmap_scaled.height(), pixmap_scaled);

}

void Maze::setVec(QList<QList<bool>> const &vec) {
    vec_ = vec;
}

