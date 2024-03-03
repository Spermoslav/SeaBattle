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


typedef unsigned int uint;
typedef unsigned short int uint16;

class Field;

class ShipMk4;
class ShipMk3;
class ShipMk2;
class ShipMk1;

class Ship : public QGroupBox
{
public:
    Ship(QWidget *parent, Field *field);

    uint getMk();

    bool getIsTarget();

    void resize();
    void rotate();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
protected:

    bool checkCollision(QPoint const &newPos, auto const &ship);

protected:

    QWidget *parent;

    Field *field;

    QPoint shipPos;
    QPoint mousePosWhenPress;
    QPoint groupBoxPosWhenPress;
    QSize shipSize;

    uint16 mk;
    int shipCenterX;
    int shipCenterY;

    bool isTarget;

    static inline std::vector<Ship*> allShips;

    enum Orientation {
        horizontal,
        vertical
    };
    Orientation orientation;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk4 : public Ship
{
public:
    ShipMk4(QWidget *parent, Field *field);

private slots:

private:

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk3 : public Ship
{
public:
    ShipMk3(QWidget *parent, Field *field);

private slots:

private:

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk2 : public Ship
{
public:
    ShipMk2(QWidget *parent, Field *field);

private slots:

private:

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk1 : public Ship
{
public:
    ShipMk1(QWidget *parent, Field *field);

private slots:

private:

};

#endif // Ship_H
