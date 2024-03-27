#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPainter>

typedef unsigned int uint;
typedef unsigned short int uint16;

class Widget;
class Ship;


class Field : public QGroupBox
{
    Q_OBJECT
public:
    Field(Widget *parent);

    int getSquareSize() const;
    uint getSquareCount() const;

    void reSize();

    void updateSquareSize();

    void randomMoveAllShips();

    virtual void spawnShips() = 0;

    QPoint findNearSquarePos(const QPoint &pos);
    QPoint findSquarePos(const QPoint &pos);

    std::vector<Ship*> getAllShips();

    Widget &getParent() const;

    void takeMissHit(const QPoint &hitPos);

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

protected:
    Widget *parent;

    std::vector<Ship*> allShips;
    std::list<QPoint> missHits;

    int squareSize;
    uint const squareCount = 10;
};

class PlayerField : public Field
{
    Q_OBJECT
public:
    PlayerField(Widget *parent);

    void spawnShips() override;
private slots:
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
