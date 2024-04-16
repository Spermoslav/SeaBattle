#include "bot.h"
#include "widget.h"
#include "field.h"
#include "tools.h"

Bot::Bot(Widget *game) noexcept
{
    field = game->getFieldBot();
    playerField = game->getFieldPlayer();
}

void Bot::motion() noexcept
{
    if(targetShip) {
        makeHit_whenFoundShip();

    }
    else {
        if(missHitOrShipHit()){
               findTargetShip();
               if(targetShip) {
                   firstShipHit = findPosForMakeShipHit();
                   lastShipHit = firstShipHit;
                   if(targetShip->takeDamage(lastShipHit)) {
                       targetShip = nullptr;
                   }
               }
               else qDebug() << "targetShip == nullptr";
        }
        else {
            playerField->takeMissHit(findPosForMakeMissHit());
        }
    }

}

bool Bot::missHitOrShipHit() noexcept
{
    float remainedShipsSqCount = 0; // кол-во оставшихся квадратов живых кораблей
    for(auto const &rs : playerField->getRemainedShips()) {
        remainedShipsSqCount += rs->getMk();
        rs->getMk();
    }
    size_t notTouchSquaresCount = field->squaresCount - field->shipsSquaresCount - playerField->getMissHits().size() ; //кол-во не задействованных квадратов
    float hitChanse = remainedShipsSqCount / notTouchSquaresCount * 100; // шанс попадания
    qDebug() << remainedShipsSqCount / notTouchSquaresCount;
    if(hitChanse >= rand() % 100) return true;
    return false;
}

QPoint Bot::findPosForMakeMissHit() noexcept
{
    QPoint hitPos;
    for(size_t i = 0; i < 100; ++i) {
        hitPos = QPoint(rand() % playerField->width(), rand() % playerField->height());
        if(!playerField->isShipOn(hitPos) && !playerField->isMissHitOn(hitPos)) return hitPos;
    }
}

QPoint Bot::findPosForMakeShipHit() noexcept // peredelat
{
    if(targetShip && !targetShip->getIsDestroy()) {
        QPoint hitPos;
        if(targetShip->getOrientation() == vertical){
            for(size_t i = 0; i < 100; ++i) {
                hitPos = QPoint(rand() % targetShip->width(), rand() % targetShip->height());
                for(auto const &dm : targetShip->damagedSquares()) {
                    if(hitPos.y() < dm->y() || hitPos.y() > dm->y() + dm->height()) {
                       return hitPos;
                    }
                }
            }
        }
        else {
            for(size_t i = 0; i < 100; ++i) {
                hitPos = QPoint(rand() % targetShip->width(), rand() % targetShip->height());
                for(auto const &dm : targetShip->damagedSquares()) {
                    if(hitPos.x() < dm->x() || hitPos.x() > dm->x() + dm->width()) {
                       return hitPos;
                    }
                }
            }
        }
    }
    return QPoint();
}

void Bot::makeHit_whenFoundShip() noexcept
{
    if(foundOrientation) {
        if(targetShip->getOrientation() == vertical) {
            makeVerticalHits();
        }
        else {
            makeHorizontalHits();
        }
    }

    else {
        if(hitDirection) {
            if(makeRightHit()) return;
            if(makeDownHit()) return;
            hitDirection = false;
            if(makeLeftHit()) return;
            makeUpHit();
        }
        else {
            if(makeLeftHit()) return;
            if(makeUpHit()) return;
            hitDirection = true;
            if(makeRightHit()) return;
            makeDownHit();
        }
    }
}

void Bot::findTargetShip() noexcept
{
    targetShip = playerField->getRemainedShips()[rand() % playerField->getRemainedShips().size()];
}

QPoint Bot::convertFieldPos_to_ShipPos(const QPoint &pos) noexcept
{
    if(targetShip) return pos - targetShip->pos();
    return pos;
}

void Bot::reset() noexcept
{
    targetShip = nullptr;
    hitDirection = rand() % 2;
    foundOrientation = false;
}

void Bot::makeVerticalHits() noexcept
{
    QPoint hitPos = targetShip->pos() + lastShipHit;
    if(hitDirection) {
        if(makeDownHit()) return;
        lastShipHit = firstShipHit;
        hitDirection = false;
        makeUpHit();
    }
    else {
        if(makeUpHit()) return;
        lastShipHit = firstShipHit;
        hitDirection = true;
        makeDownHit();
    }
}

void Bot::makeHorizontalHits() noexcept
{
    if(hitDirection) {
        if(makeRightHit()) return;
        lastShipHit = firstShipHit;
        hitDirection = false;
        makeLeftHit();
    }
    else {
        if(makeLeftHit()) return;
        lastShipHit = firstShipHit;
        hitDirection = true;
        makeRightHit();
    }
}

bool Bot::makeLeftHit() noexcept
{
    QPoint hitPos = targetShip->pos() + lastShipHit - QPoint(playerField->getSquareSize(), 0);
    return tryMakeHit(hitPos);
}

bool Bot::makeUpHit() noexcept
{
    QPoint hitPos = targetShip->pos() + lastShipHit - QPoint(0, playerField->getSquareSize());
    return tryMakeHit(hitPos);
}

bool Bot::makeRightHit() noexcept
{
    QPoint hitPos = targetShip->pos() + lastShipHit + QPoint(playerField->getSquareSize(), 0);
    return tryMakeHit(hitPos);
}

bool Bot::makeDownHit() noexcept
{
    QPoint hitPos = targetShip->pos() + lastShipHit + QPoint(0, playerField->getSquareSize());
    return tryMakeHit(hitPos);
}

bool Bot::tryMakeHit(QPoint &hitPos) noexcept
{
    if(targetShip) {
        if(playerField->isShipOn(hitPos)) {
            hitPos = convertFieldPos_to_ShipPos(hitPos);
            lastShipHit = hitPos;
            foundOrientation = true;
            if(targetShip->takeDamage(hitPos)) {
                targetShip = nullptr;
                foundOrientation = false;
            }
            return true;
        }
        else if(!playerField->isMissHitOn(hitPos) && !playerField->isOutField(hitPos)){
            playerField->takeMissHit(hitPos);
            return true;
        }
    }
}
