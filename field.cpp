#include "field.h"
#include "ships.h"
#include "widget.h"
#include <algorithm>

Field::Field(Widget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;

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
    if(!parent->gameStart) {
        for( auto const &ship : allShips)
            ship->randomMove();
    }
}

std::vector<Ship *> Field::getAllShips()
{
    return allShips;
}

Widget &Field::getParent() const
{
    return *parent;
}

void Field::takeMissHit(const QPoint &hitPos)
{
    if(parent->gameStart) {
        missHits.push_back(findSquarePos(hitPos));
        update();
    }
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

PlayerField::PlayerField(Widget *parent)
    : Field(parent)
{

}

void PlayerField::spawnShips()
{
    if(allShips.empty()) {
        for(std::size_t i = 0; i < 10; i ++) {
            allShips.push_back(new PlayerShip(this));
        }
    }
}

BotField::BotField(Widget *parent)
    : Field(parent)
{

}

void BotField::spawnShips()
{
    if(allShips.empty()) {
        for(std::size_t i = 0; i < 10; i ++) {
            allShips.push_back(new BotShip(this));
        }
    }
}

void BotField::mousePressEvent(QMouseEvent *e)
{
    takeMissHit(e->pos());
}
