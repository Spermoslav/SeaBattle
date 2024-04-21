#include "bot.h"
#include "field.h"
#include "ships.h"
#include "tools.h"
#include <thread>

Bot::Bot(Widget *game) noexcept
{

    this->game = game;
    playerField = game->fieldPlayer;

    mTimer = new MotionTimer(this, 500);
}

void Bot::activate()
{
    if(game->getWhoMove() == Gamer::bot) mTimer->start();
}

void Bot::motion() noexcept
{
    if(targetShip) {
        makeHit_whenFoundShip();
    }
    else {

#ifdef BOT_UNMISS_FIRSTHIT
        makeFirstShipHit();
#else
        if(missHitOrShipHit()){
               makeFirstShipHit();
        }
        else {
            playerField->takeMissHit(findPosForMakeMissHit());
            mTimer->stop();
            game->changeWhoMove();

        }
#endif
    }

}

bool Bot::missHitOrShipHit() noexcept
{
    float remainedShipsSqCount = 0; // кол-во оставшихся квадратов живых кораблей
    for(const auto &rs : playerField->getRemainedShips()) {
        remainedShipsSqCount += rs->getMk();
        rs->getMk();
    }
    size_t notTouchSQUARES_COUNT = Field::SQUARES_COUNT - Field::SHIPS_SQUARES_COUNT - playerField->getMissHits().size(); //кол-во не задействованных квадратов
    float hitChanse = remainedShipsSqCount / notTouchSQUARES_COUNT * 100; // шанс попадания
    int er = rand() % 100;
    qDebug() << hitChanse << er << bool(hitChanse >= er);
    return hitChanse >= er;
}

QPoint Bot::findPosForMakeMissHit() noexcept //
{
    QPoint hitPos;
    for(size_t i = 0; i < 100; ++i) {
        hitPos = QPoint(rand() % playerField->width(), rand() % playerField->height());
        if(!playerField->isShipOn(hitPos) && !playerField->isMissHitOn(hitPos)) return hitPos;
    }
}

QPoint Bot::findPosForMakeShipHit() noexcept //
{
    if(targetShip && !targetShip->getIsDestroy()) {
        QPoint hitPos;
        if(targetShip->getOrientation() == vertical){
            for(size_t i = 0; i < 100; ++i) {
                hitPos = QPoint(rand() % targetShip->width(), rand() % targetShip->height());
                for(const auto &dm : targetShip->damagedSquares()) {
                    if(hitPos.y() < dm->y() || hitPos.y() > dm->y() + dm->height()) {
                       return hitPos;
                    }
                }
            }
        }
        else {
            for(size_t i = 0; i < 100; ++i) {
                hitPos = QPoint(rand() % targetShip->width(), rand() % targetShip->height());
                for(const auto &dm : targetShip->damagedSquares()) {
                    if(hitPos.x() < dm->x() || hitPos.x() > dm->x() + dm->width()) {
                       return hitPos;
                    }
                }
            }
        }
    }
    return QPoint();
}

bool Bot::makeHit_whenFoundShip() noexcept
{
    if(foundOrientation) {
        if(targetShip->getOrientation() == vertical) {
            makeVerticalHits();
        }
        else {
            return makeHorizontalHits();
        }
    }
    else {
        if(hitDirection) {
            if(makeRightHit()) return true;
            if(makeDownHit())  return true;
            hitDirection = false;
            if(makeLeftHit())  return true;
            return makeUpHit();
        }
        else {
            if(makeLeftHit())  return true;
            if(makeUpHit())    return true;
            hitDirection = true;
            if(makeRightHit()) return true;
            return makeDownHit();
        }
    }
    return false;
}

void Bot::findTargetShip() noexcept
{
    targetShip = playerField->getRemainedShips()[rand() % playerField->getRemainedShips().size()];
}

void Bot::makeFirstShipHit()
{
    if(targetShip) return;
    findTargetShip();
    if(targetShip) {
        firstShipHit = findPosForMakeShipHit();
        lastShipHit = firstShipHit;
        if(targetShip->takeDamage(lastShipHit)) {
            targetShip = nullptr;
            return;
        }
        mTimer->start();
    }
    else qDebug() << "targetShip == nullptr";
}

QPoint Bot::convertFieldPos_to_ShipPos(const QPoint &pos) noexcept
{
    if(targetShip) return pos - targetShip->pos();
    return pos;
}

void Bot::reset() noexcept
{
    mTimer->stop();
    targetShip = nullptr;
    hitDirection = rand() % 2;
    foundOrientation = false;
}

bool Bot::makeVerticalHits() noexcept
{
    if(hitDirection) {
        if(makeDownHit()) return true;
        lastShipHit = firstShipHit;
        hitDirection = false;
        return makeUpHit();
    }
    else {
        if(makeUpHit()) return true;
        lastShipHit = firstShipHit;
        hitDirection = true;
        return makeDownHit();
    }
}

bool Bot::makeHorizontalHits() noexcept
{
    if(hitDirection) {
        if(makeRightHit()) return true;
        lastShipHit = firstShipHit;
        hitDirection = false;
        return makeLeftHit();
    }
    else {
        if(makeLeftHit()) return true;
        lastShipHit = firstShipHit;
        hitDirection = true;
        return makeRightHit();
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
            mTimer->start();
            return true;
        }
        else if(!playerField->isMissHitOn(hitPos) && !playerField->isOutField(hitPos)){
            playerField->takeMissHit(hitPos);
            mTimer->stop();
            game->changeWhoMove();
            return true;
        }
    }
    return false;
}


Bot::MotionTimer::MotionTimer(Bot *bot, uint rd)
{
    this->bot = bot;
    run_delay = rd;
}

void Bot::MotionTimer::start()
{
    if(isStart) return;
    isStart = true;
    std::thread th(&MotionTimer::run, this);
    th.detach();
}

void Bot::MotionTimer::run()
{
    qDebug() << " run ";
    std::srand(std::time(nullptr));
    while(isStart) {
        std::this_thread::sleep_for(std::chrono::milliseconds(run_delay));
        if(isStart) bot->motion();
        else break;
    }
}
