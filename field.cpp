#include "field.h"
#include "ships.h"
#include "tools.h"
#include "bot.h"
#include <algorithm>

Field::Field(Widget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
    allShips.reserve(10);
    reSize();
}

void Field::reSize() noexcept
{
    const int fieldSize = std::min(parent->width() / 2, (parent->height() - parent->infoBar->height()) / 2);
    resize(fieldSize, fieldSize);
    updateSquareSize();
    for(auto &mh : missHits) {
        mh = findNearSquarePos(mh);
    }
    repaint();
}

void Field::updateSquareSize() noexcept
{
    squareSize = width() / ROWS_COUNT;
}

void Field::randomMoveAllShips() noexcept
{
    for(const auto &ship : allShips) ship->randomMove();
}

void Field::eraseRemainedShip(const Ship* ship) noexcept
{
    if(!remainedShips.empty()) {
        remainedShips.erase(std::find(remainedShips.begin(), remainedShips.end(), ship));
    }
}

void Field::addMissHitsAroundDestroyShip(const Ship *ship) noexcept
{
    QPoint missHitPos = ship->pos() - QPoint(squareSize, squareSize);
    takeMissHit(missHitPos);
    if(ship->getOrientation() == vertical) {
        missHitPos += QPoint(squareSize, 0);
        takeMissHit(missHitPos);
        missHitPos += QPoint(squareSize, 0);
        takeMissHit(missHitPos);
        for(size_t i = 0; i <= ship->getMk(); i++) {
            missHitPos += QPoint(0, squareSize);
            takeMissHit(missHitPos);
        }
        missHitPos -= QPoint(squareSize, 0);
        takeMissHit(missHitPos);
        missHitPos -= QPoint(squareSize, 0);
        takeMissHit(missHitPos);
        for(size_t i = 0; i < ship->getMk(); i++) {
            missHitPos -= QPoint(0, squareSize);
            takeMissHit(missHitPos);
        }
    }
    else {
        for(size_t i = 0; i <= ship->getMk(); i++) {
            missHitPos += QPoint(squareSize, 0);
            takeMissHit(missHitPos);
        }
        missHitPos += QPoint(0, squareSize);
        takeMissHit(missHitPos);
        missHitPos += QPoint(0, squareSize);
        takeMissHit(missHitPos);
        for(size_t i = 0; i <= ship->getMk(); i++) {
            missHitPos -= QPoint(squareSize, 0);
            takeMissHit(missHitPos);
        }
        missHitPos -= QPoint(0, squareSize);
        takeMissHit(missHitPos);
    }
}

void Field::takeMissHit(const QPoint &hitPos) noexcept
{
    if(!isMissHitOn(hitPos) && !isOutField(hitPos) && !isShipOn(hitPos)) {
        missHits.push_back(findSquarePos(hitPos));
        update();
    }
}

void Field::reset() noexcept
{
    remainedShips.clear();
    for(auto &ship : allShips) {
        ship->reset();
        remainedShips.push_back(ship);
    }
    missHits.clear();
    update();
}

QPoint Field::findNearSquarePos(const QPoint &pos) const noexcept
{
    return QPoint((pos.x() + squareSize / 2) / squareSize,
                  (pos.y() + squareSize / 2) / squareSize) * squareSize;
}

QPoint Field::findSquarePos(const QPoint &pos) const noexcept
{
    return QPoint((pos.x() / squareSize),
                  (pos.y() / squareSize)) * squareSize;
}

bool Field::isShipOn(const QPoint &pos) const noexcept
{
    for(auto const &ship : allShips) {
        if(pos == ship->pos()) return true;
        else if(pos.x() >= ship->x() && pos.x() < ship->x() + ship->width() &&
           pos.y() >= ship->y() && pos.y() < ship->y() + ship->height()){
            return true;
        }
    }
    return false;
}

bool Field::isMissHitOn(const QPoint &pos) const noexcept
{
    for(auto const &mh : missHits) {
        if(mh == findSquarePos(pos)) {
            return true;
        }
    }
    return false;
}

bool Field::isOutField(const QPoint &pos) const noexcept
{
    return pos.x() < 0 || pos.y() < 0 || pos.x() > width() || pos.y() > height();
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
    for(uint i = 0; i < ROWS_COUNT; i++) {
        for(uint j = 0; j < ROWS_COUNT; j++) {
            p.drawRect(i * squareSize, j * squareSize, squareSize, squareSize);
        }
    }
    p.setBrush(Qt::cyan);
    for(auto const &mh : missHits) {
        p.drawEllipse(mh.x(), mh.y(), squareSize, squareSize);
    }
    p.end();
}


void PlayerField::shipDestroyed(const Ship *ship) noexcept
{
    eraseRemainedShip(ship);
    addMissHitsAroundDestroyShip(ship);
    if(remainedShips.empty()) parent->finishGame(Gamer::bot);
}

void PlayerField::spawnShips() noexcept
{
    if(allShips.empty()) {
        for(std::size_t i = 0; i < SHIP_COUNT; i ++) {
            allShips.push_back(new PlayerShip(this));
            remainedShips.push_back(allShips[i]);
        }
    }

}

void PlayerField::mousePressEvent(QMouseEvent *e)
{

    qDebug() << isShipOn(e->pos());
    qDebug() << isMissHitOn(e->pos());
}


void BotField::shipDestroyed(const Ship *ship) noexcept
{
    eraseRemainedShip(ship);
    addMissHitsAroundDestroyShip(ship);
    if(remainedShips.empty()) parent->finishGame(Gamer::player);
}

void BotField::spawnShips() noexcept
{
    if(allShips.empty()) {
        for(std::size_t i = 0; i < 10; i ++) {
            allShips.push_back(new BotShip(this));
            remainedShips.push_back(allShips[i]);
        }
    }
}

void BotField::mousePressEvent(QMouseEvent *e)
{
    if(parent->getGameIsStart() && parent->getWhoMove() == Gamer::player) {
        takeMissHit(e->pos());
        parent->changeWhoMove();
        parent->getBot()->activate();
    }
}
