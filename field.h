#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPainter>

typedef unsigned int uint;

class Ships;
class ShipMk4;
class ShipMk3;
class ShipMk2;
class ShipMk1;


class Field : public QGroupBox
{
    Q_OBJECT
public:
    Field(QWidget *parent);

    int getSquareSize();
    uint getSquareCount();

    void updateSquareSize();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    QWidget *parent;

    ShipMk1 *shipMk1;
    ShipMk2 *shipMk2;
    ShipMk3 *shipMk3;
    ShipMk4 *shipMk4;

    uint squareSize;
    uint const squareCount = 10;
};

#endif // FIELD_H
