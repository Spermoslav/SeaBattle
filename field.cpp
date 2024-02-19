#include "field.h"
#include "ships.h"

#include <algorithm>

Field::Field(QWidget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;

    squareSize = std::min(parent->width(), parent->height()) / squareCount;
}

int Field::getSquareSize()
{
    return squareSize;
}

const int Field::getSquareCount()
{
    return squareCount;
}

void Field::updateSquareSize()
{
    squareSize = std::min(parent->width(), parent->height()) / squareCount;
}

void Field::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    repaint();
}

void Field::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p;
    p.begin(this);
    p.drawRect(0, 0, width() - 2, height() - 2);
    for(int i = 0; i < squareCount; i++) {
        for(int j = 0; j < squareCount; j++) {
            p.drawRect(i * squareSize, j * squareSize, squareSize, squareSize);
        }
    }
    p.end();
}
