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
class Damage;
class ShipMk4;
class ShipMk3;
class ShipMk2;
class ShipMk1;

class Ship : public QGroupBox
{
    Q_OBJECT
public:
    Ship() = default;

    Ship(Field *field);

    uint          getMk();

    inline Field &getField() const;

    bool          getIsTarget();

    void          resize();
    void          rotate();

    void          randomMove();
    void takeDamage(const QPoint &damagePos);

    bool checkCollision(QPoint const &newPos, auto const &ship);
    bool checkShipCollision(QPoint const &newPos, auto const &ship);
    bool checkFieldCollision(QPoint const &newPos);

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
private:

    QPoint findPosForDamage(const QPoint &pos);

private:

    QWidget *parent;

    Field *field;

    QPoint shipPos;
    QPoint mousePosWhenPress;
    QPoint groupBoxPosWhenPress;

    QSize shipSize;

    std::vector<Damage*> damage;

    uint16 mk;
    uint16 destroyItems;
    int shipCenterX;
    int shipCenterY;
    static inline int shipCount = 0;

    bool isTarget;
    bool isPlayerField;
    bool isDestroy;

    enum Orientation {
        horizontal,
        vertical
    };
    Orientation orientation;


};

class Damage : public QWidget
{
    Q_OBJECT
public:
    Damage() = default;

    Damage(Ship* parent);

    void resize();
public slots:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
private:
    Ship* parent;
};

#endif // Ship_H
