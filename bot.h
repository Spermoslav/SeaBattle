#ifndef BOT_H
#define BOT_H

#include <QPoint>
#include <QObject>
#include "ships.h"

class Widget;
class BotField;
class PlayerField;
class PlayerShip;
class Ship;

class Bot
{

public:
    Bot(Widget *game) noexcept;

    void motion() noexcept;
    void reset()  noexcept;

private:

    QPoint findPosForMakeMissHit() noexcept;
    QPoint findPosForMakeShipHit() noexcept;
    QPoint convertFieldPos_to_ShipPos(const QPoint &pos) noexcept;

    void findTargetShip()        noexcept;

    void makeHit_whenFoundShip() noexcept;
    void makeVerticalHits()      noexcept;
    void makeHorizontalHits()    noexcept;
    bool makeLeftHit()           noexcept;
    bool makeUpHit()             noexcept;
    bool makeRightHit()          noexcept;
    bool makeDownHit()           noexcept;
    bool tryMakeHit(QPoint &hitPos) noexcept;

    bool missHitOrShipHit()      noexcept;

    BotField *field;
    PlayerField *playerField;
    QPoint lastShipHit;
    QPoint firstShipHit;
    bool hitDirection = rand() % 2; // true - down or right, false - up or left
    bool foundOrientation = false;

    quint8 hard;

    Ship *targetShip = nullptr;
};
#endif // BOT_H
