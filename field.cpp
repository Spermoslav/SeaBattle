#include "field.h"
#include "ships.h"

#include <algorithm>

Field::Field(QWidget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
    ++fieldCount;
    if(fieldCount == 1) isPlayerField = true;
    else isPlayerField = false;

    updateSquareSize();
    int fieldSize = squareSize * squareCount;
    resize(fieldSize, fieldSize);
    for(std::size_t i = 0; i < 10; i ++) {
        allShips.push_back(new Ship(this));

    }
}

int Field::getSquareSize() const
{
    return squareSize;
}

uint Field::getSquareCount() const
{
    return squareCount;
}

bool Field::getIsPlayerField()
{
    return isPlayerField;
}

void Field::updateSquareSize()
{
    squareSize = std::min(parent->width() / 2, parent->height() / 2) / squareCount;
}

void Field::randomMoveAllShips()
{
    for( auto const &ship : allShips)
            ship->randomMove();
}

std::vector<Ship *> Field::getAllShips()
{
    return allShips;
}

void Field::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    repaint();
    for(auto const &ship : allShips) {
        ship->resize();
    }
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
