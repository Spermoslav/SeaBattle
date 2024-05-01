#ifndef BOT_H
#define BOT_H

#include <QPoint>
#include <QObject>
#include "widget.h"

class Bot
{

public:
    Bot(Widget *game);

    void activate();
    void motion();
    void reset();

private:

    QPoint findPosForMakeMissHit();
    QPoint findPosForMakeShipHit();
    QPoint convertFieldPos_to_ShipPos(const QPoint &pos);

    void findTargetShip();

    void makeFirstShipHit();
    bool makeHit_whenFoundShip();
    bool makeVerticalHits();
    bool makeHorizontalHits();
    bool makeLeftHit();
    bool makeUpHit();
    bool makeRightHit();
    bool makeDownHit();
    bool tryMakeHit(QPoint &hitPos);

    bool missHitOrShipHit(); // false - miss hit, true - ship hit


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
