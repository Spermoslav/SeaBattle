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
    Ship(Field *field);

    void resize();
    void rotate();
    void reset();
    void randomMove();

    virtual bool takeDamage(const QPoint &damagePos) = 0; // true == destroy

    bool checkCollision(const QPoint &newPos, const Ship *ship) const;
    bool checkShipCollision(const QPoint &newPos, const Ship *ship) const;
    bool checkFieldCollision(const QPoint &newPos) const;

    quint8 getMk()      const { return mk;          }
    bool getIsTarget()  const { return isTarget;    }
    bool getIsDestroy() const { return isDestroy;   }
    Orientation getOrientation() const { return orientation; }

    const std::vector<Damage*> &damagedSquares() const { return damage; }

    const Field *getField() const { return field; }

    const static QColor PLAYER_COLOR;
    const static QColor BOT_COLOR;

private slots:
    void resizeEvent(QResizeEvent *e) override;
protected:

    QPoint findPosForDamage(const QPoint &pos) const;

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
    quint8 destroyItems = 0;
    int shipCenterX;
    int shipCenterY;

    bool isTarget  = false;
    bool isDestroy = false;

    Orientation orientation;
};

class PlayerShip : public Ship
{
    Q_OBJECT
public:
    PlayerShip(Field *field) : Ship(field) {}

    bool takeDamage(const QPoint &damagePos) override;

private slots:
    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e)   override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e)    override;
};

class BotShip : public Ship
{
    Q_OBJECT
public:
    BotShip(Field *field) : Ship(field) {}

    bool takeDamage(const QPoint &damagePos) override;

private slots:
    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
};

class Damage : public QWidget
{
    Q_OBJECT
public:
    Damage(Ship* parent);

    void resize();
public slots:
    void paintEvent(QPaintEvent *e)   override;
    void resizeEvent(QResizeEvent *e) override;
private:
    Ship* parent;
};

#endif // Ship_H
