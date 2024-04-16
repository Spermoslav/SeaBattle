#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPainter>

class Widget;
class Ship;
class PlayerShip;

class Field : public QGroupBox
{
    Q_OBJECT
public:
    Field(Widget *parent);
    void reset();
    void reSize();
    void updateSquareSize();
    void randomMoveAllShips();
    void takeMissHit(const QPoint &hitPos);
    void eraseRemainedShip(const Ship* ship);
    void addMissHitsAroundDestroyShip(const Ship* ship);

    virtual void spawnShips() = 0;

    QPoint findNearSquarePos(const QPoint &pos);
    QPoint findSquarePos(const QPoint &pos);

    bool isShipOn(const QPoint &pos) noexcept;
    bool isMissHitOn(const QPoint &pos) noexcept;
    bool isOutField(const QPoint &pos) noexcept;

    int getSquareSize() const;

    std::vector<Ship*> &getAllShips();
    std::vector<Ship*> &getRemainedShips();
    std::list<QPoint> &getMissHits();

    Widget &getParent() const;

    const static quint8 squaresCount = 100;
    const static quint8 rowsCount = 10;
    const static quint8 shipCount = 10;
    const static quint8 shipsSquaresCount = 20;


private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

protected:
    Widget *parent;

    std::vector<Ship*> allShips;
    std::vector<Ship*> remainedShips;
    std::list<QPoint> missHits;

    int squareSize;

};

class PlayerField : public Field
{
    Q_OBJECT
public:
    PlayerField(Widget *parent);

    void spawnShips() override;

private slots:
    void mousePressEvent(QMouseEvent *e) override;

private:

};

class BotField : public Field
{
    Q_OBJECT
public:
    BotField(Widget *parent);

    void spawnShips() override;
private slots:
    void mousePressEvent(QMouseEvent *e) override;
};
#endif // FIELD_H
