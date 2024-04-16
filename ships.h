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

enum Orientation {
    horizontal,
    vertical
};

class Ship : public QGroupBox
{
    Q_OBJECT
public:
    Ship() = default;

    Ship(Field *field);

    uint          getMk() const;

    inline Field *getField() const;

    std::vector<Damage*> &damagedSquares();

    bool getIsTarget() const;
    bool getIsDestroy() const;
    void resize();
    void rotate();

    void          randomMove();
    virtual bool takeDamage(const QPoint &damagePos) = 0;

    bool checkCollision(const QPoint &newPos, const auto &ship) const;
    bool checkShipCollision(const QPoint &newPos, const auto &ship) const;
    bool checkFieldCollision(const QPoint &newPos) const;

    void reset();

    Orientation getOrientation() const;

private slots:
    void resizeEvent(QResizeEvent *e) override;
protected:

    QPoint findPosForDamage(const QPoint &pos) const;

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

    Orientation orientation;
};

class PlayerShip : public Ship
{
    Q_OBJECT
public:

    PlayerShip(Field *field);

    bool takeDamage(const QPoint &damagePos) override;

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

    bool takeDamage(const QPoint &damagePos) override;

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
