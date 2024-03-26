#include "field.h"
#include "ships.h"
#include "widget.h"
#include <algorithm>

Field::Field(Widget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
    ++fieldCount;
    if(fieldCount == 1) isPlayerField = true;
    else isPlayerField = false;

    reSize();
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

void Field::reSize()
{
    const int fieldSize = std::min(parent->width() / 2, (parent->height() - parent->getInfoBar().height()) / 2);
    resize(fieldSize, fieldSize);
    updateSquareSize();
    for(auto &mh : missHits) {
        mh = findNearSquarePos(mh);
    }
    repaint();
}

void Field::updateSquareSize()
{
    squareSize = width() / squareCount;
}

void Field::randomMoveAllShips()
{
    for( auto const &ship : allShips)
        ship->randomMove();
}

void Field::spawnShips()
{
    if(allShips.empty()) {
        for(std::size_t i = 0; i < 10; i ++) {
            allShips.push_back(new Ship(this));
        }
    }
}

std::vector<Ship *> Field::getAllShips()
{
    return allShips;
}

void Field::mousePressEvent(QMouseEvent *e)
{
    missHits.push_back(findSquarePos(e->pos()));
    update();
}

QPoint Field::findNearSquarePos(const QPoint &pos)
{
    return QPoint((pos.x() + squareSize / 2) / squareSize,
                  (pos.y() + squareSize / 2) / squareSize) * squareSize;
}

QPoint Field::findSquarePos(const QPoint &pos)
{
    return QPoint((pos.x() / squareSize),
                  (pos.y() / squareSize)) * squareSize;
}

void Field::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
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
    p.setBrush(Qt::cyan);
    for(auto const &mh : missHits) {
        p.drawEllipse(mh.x(), mh.y(), squareSize, squareSize);
    }
    p.end();
}
