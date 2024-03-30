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

class Field;
class Damage;
class PlayerShip;
class BotShip;
class InfoBar;

class Ship : public QGroupBox
{
    Q_OBJECT
public:
    Ship() = default;

    Ship(Field *field);

    uint          getMk();

    inline Field *getField() const;

    bool          getIsTarget();

    void          resize();
    void          rotate();

    void          randomMove();
    virtual void takeDamage(const QPoint &damagePos) = 0;

    bool checkCollision(QPoint const &newPos, auto const &ship);
    bool checkShipCollision(QPoint const &newPos, auto const &ship);
    bool checkFieldCollision(QPoint const &newPos);

    void reset();

private slots:
    void resizeEvent(QResizeEvent *e) override;
protected:

    QPoint findPosForDamage(const QPoint &pos);

protected:

    Field *field;

    QPoint shipPos;
    QPoint mousePosWhenPress;
    QPoint groupBoxPosWhenPress;

    QSize shipSize;

    std::vector<Damage*> damage;
    InfoBar *infoBar;

    quint16 mk;
    quint16 destroyItems;
    int shipCenterX;
    int shipCenterY;

    bool isTarget;
    bool isDestroy;

    enum Orientation {
        horizontal,
        vertical
    };
    Orientation orientation;


};

class PlayerShip : public Ship
{
    Q_OBJECT
public:

    PlayerShip(Field *field);

    void takeDamage(const QPoint &damagePos) override;

private slots:
    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

class BotShip : public Ship
{
    Q_OBJECT
public:

    BotShip(Field *field);

    void takeDamage(const QPoint &damagePos) override;

private slots:
    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
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
