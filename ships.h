#ifndef Ship_H
#define Ship_H


#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QMouseEvent>
#include <QKeyEvent>
#include "widget.h"

enum Orientation {
    horizontal,
    vertical
};

class Ship : public QGroupBox
{
    Q_OBJECT
public:
    Ship(Field *field) noexcept;

    void resize() noexcept;
    void rotate() noexcept;
    void reset()  noexcept;
    void randomMove() noexcept;

    virtual bool takeDamage(const QPoint &damagePos) noexcept = 0;

    bool checkCollision(const QPoint &newPos, const Ship *ship) const noexcept;
    bool checkShipCollision(const QPoint &newPos, const Ship *ship) const noexcept;
    bool checkFieldCollision(const QPoint &newPos) const noexcept;

    quint8 getMk() const noexcept { return mk; }
    bool getIsTarget()  const noexcept {return isTarget; }
    bool getIsDestroy() const noexcept { return isDestroy; }
    const Field *getField() const noexcept { return field; }
    Orientation getOrientation() const noexcept { return orientation; }
    const std::vector<Damage*> &damagedSquares() const noexcept { return damage; }


private slots:
    void resizeEvent(QResizeEvent *e) noexcept override;
protected:

    QPoint findPosForDamage(const QPoint &pos) const noexcept;

    void turn(); // поворот без проверки на коллизию

protected:
    Field *field;

    QPoint shipPos;
    QPoint mousePosWhenPress;
    QPoint groupBoxPosWhenPress;

    QSize shipSize;

    std::vector<Damage*> damage;
    InfoBar *infoBar;

    quint8 mk;
    quint8 destroyItems;
    int shipCenterX;
    int shipCenterY;

    bool isTarget;
    bool isDestroy;

    Orientation orientation;
};

class PlayerShip : public Ship
{
    Q_OBJECT
public:
    PlayerShip(Field *field) noexcept;

    bool takeDamage(const QPoint &damagePos) noexcept override;

private slots:
    void paintEvent(QPaintEvent *e) noexcept override;

    void mousePressEvent(QMouseEvent *e) noexcept override;
    void mouseReleaseEvent(QMouseEvent *e) noexcept override;
    void mouseMoveEvent(QMouseEvent *e) noexcept override;
};

class BotShip : public Ship
{
    Q_OBJECT
public:
    BotShip(Field *field) noexcept;

    bool takeDamage(const QPoint &damagePos) noexcept override;

private slots:
    void paintEvent(QPaintEvent *e) noexcept override;

    void mousePressEvent(QMouseEvent *e) noexcept override;
};

class Damage : public QWidget
{
    Q_OBJECT
public:
    Damage(Ship* parent) noexcept;

    void resize() noexcept;
public slots:
    void paintEvent(QPaintEvent *e) noexcept override;
    void resizeEvent(QResizeEvent *e) noexcept override;
private:
    Ship* parent;
};

#endif // Ship_H
