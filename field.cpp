#include "field.h"
#include "ships.h"

#include <algorithm>

Field::Field(QWidget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;

    updateSquareSize();

    shipMk1 = new ShipMk1(this, this);
    shipMk2 = new ShipMk2(this, this);
    shipMk3 = new ShipMk3(this, this);
    shipMk4 = new ShipMk4(this, this);
}

int Field::getSquareSize()
{
    return squareSize;
}

uint Field::getSquareCount()
{
    return squareCount;
}

void Field::updateSquareSize()
{
    squareSize = std::min(parent->width() / 2, parent->height() / 2) / squareCount;
}

void Field::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    repaint();
    shipMk1->resize();
    shipMk2->resize();
    shipMk3->resize();
    shipMk4->resize();
}

void Field::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p;
    p.begin(this);
    p.drawRect(0, 0, width() - 2, height() - 2);
    for(uint i = 0; i < squareCount; i++) {
        for(uint j = 0; j < squareCount; j++) {
            p.drawRect(i * squareSize, j * squareSize, squareSize, squareSize);
        }
    }
    p.end();
}
