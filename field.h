#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPainter>
#include "widget.h"

class Field : public QGroupBox
{
    Q_OBJECT
public:
    Field(Widget *parent);
    void reset()  noexcept;
    void resetFreeSquares();
    void reSize() noexcept;

    void updateSquareSize()   noexcept;
    void randomMoveAllShips() noexcept;
    void takeMissHit(const QPoint &hitPos)   noexcept;

    virtual void shipDestroyed(const Ship *ship) = 0;
    virtual void spawnShips() = 0;

    QPoint findNearSquarePos(const QPoint &pos) const noexcept;
    QPoint findSquarePos(const QPoint &pos)     const noexcept;

    bool isShipOn(const QPoint &pos)    const noexcept;
    bool isMissHitOn(const QPoint &pos) const noexcept;
    bool isOutField(const QPoint &pos)  const noexcept;

    int getSquareSize() const { return squareSize; }

    const std::vector<Ship*> &getAllShips()      const { return allShips;      }
    const std::vector<Ship*> &getRemainedShips() const { return remainedShips; }
    const std::list<QPoint>  &getMissHits()      const { return missHits;      }
    const std::list<QPoint>      &getFreeSquares()   const { return freeSquares;   }

    const Widget *getParent() const { return parent; }

    const static quint8 SQUARES_COUNT       = 100;
    const static quint8 ROWS_COUNT          = 10;
    const static quint8 SHIP_COUNT          = 10;
    const static quint8 SHIPS_SQUARES_COUNT = 20;


private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e)   override;

protected:
    void eraseRemainedShip(const Ship* ship) noexcept;
    void addMissHitsAroundDestroyShip(const Ship* ship) noexcept;

    Widget *parent;

    std::vector<Ship*> allShips;
    std::vector<Ship*> remainedShips;
    std::list<QPoint> missHits;
    std::list<QPoint> freeSquares;

    int squareSize;
};

class PlayerField : public Field
{
    Q_OBJECT
public:
    PlayerField(Widget *parent) : Field(parent) {}

    void shipDestroyed(const Ship *ship) noexcept override;
    void spawnShips()    noexcept override;

private slots:
    void mousePressEvent(QMouseEvent *e) override;
};

class BotField : public Field
{
    Q_OBJECT
public:
    BotField(Widget *parent) : Field(parent) {}

    void shipDestroyed(const Ship *ship) noexcept override;
    void spawnShips() noexcept override;

private slots:
    void mousePressEvent(QMouseEvent *e) override;
};
#endif // FIELD_H
