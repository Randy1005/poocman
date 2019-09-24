#include <QtGui>
#include <QtCore>

#include "maze.h"


Maze::Maze(QWidget *parent) : QWidget(parent)
{
    mazePixmap = new QPixmap(size());
}

Maze::~Maze() {
    delete(mazePixmap);
}

void Maze::paintEvent(QPaintEvent *event) {
    QPixmap pixmap(vec_.front().size(), vec_.size());
    QPainter pixmap_painter(&pixmap);

    for(int y = 0; y < vec_.size(); y++) {
        for(int x = 0; x < vec_[y].size(); x++) {
            pixmap_painter.setPen(vec_[y][x] ? QColor("black") : QColor("grey"));
            pixmap_painter.drawPoint(x, y); // Draw individual pixels
        }
    }

    QPainter painter(this);
    pixmap_scaled = pixmap.scaled(size(), Qt::KeepAspectRatio); // scale to fit the widget

    painter.drawPixmap(
        (width() - pixmap_scaled.width()) / 2,
        (height() - pixmap_scaled.height()) / 2,
        pixmap_scaled.width(), pixmap_scaled.height(), pixmap_scaled);

}

void Maze::setVec(QList<QList<bool>> const &vec) {
    vec_ = vec;
}

void Maze::mousePressEvent(QMouseEvent *event) {
    QPointF mousePosition = event->pos();
    qDebug() << "X: " << mousePosition.x() <<
                "Y: " << mousePosition.y() <<
                "RGB: " << qRed(getPixelRGB(mousePosition.x(), mousePosition.y()));
}

void Maze::renderToPixmap() {
    render(mazePixmap, QPoint(), QRegion(QRect((width() - pixmap_scaled.width()) / 2,
                                               (height() - pixmap_scaled.height()) / 2,
                                               pixmap_scaled.width(),
                                               pixmap_scaled.height())));
}

QRgb Maze::getPixelRGB(int x, int y) {
    return mazePixmap->toImage().pixel(x, y);
}


