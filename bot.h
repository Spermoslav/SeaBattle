#ifndef BOT_H
#define BOT_H

#include <QPoint>
#include <QObject>
#include "widget.h"

class Bot
{

public:
    Bot(Widget *game) noexcept;

    void activate();
    void motion() noexcept;
    void reset()  noexcept;

private:

    QPoint findPosForMakeMissHit() noexcept;
    QPoint findPosForMakeShipHit() noexcept;
    QPoint convertFieldPos_to_ShipPos(const QPoint &pos) noexcept;

    void findTargetShip()        noexcept;

    void makeFirstShipHit();
    bool makeHit_whenFoundShip() noexcept;
    bool makeVerticalHits()      noexcept;
    bool makeHorizontalHits()    noexcept;
    bool makeLeftHit()           noexcept;
    bool makeUpHit()             noexcept;
    bool makeRightHit()          noexcept;
    bool makeDownHit()           noexcept;
    bool tryMakeHit(QPoint &hitPos) noexcept;

    bool missHitOrShipHit()      noexcept; // false - miss hit, true - ship hit


    struct MotionTimer {
        MotionTimer(Bot *bot, uint delay);
        void stop() { isStart = false; }
        void start();
        void run();
        Bot *bot;
        bool isStart = false;
        uint run_delay;
    };

    PlayerField *playerField;
    Widget *game;
    Ship *targetShip = nullptr;
    MotionTimer *mTimer;
    QPoint lastShipHit;
    QPoint firstShipHit;
    bool hitDirection = rand() % 2; // true - down or right, false - up or left
    bool foundOrientation = false;

    quint8 hard;
};
#endif // BOT_H
