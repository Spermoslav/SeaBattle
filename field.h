#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPainter>

typedef unsigned int uint;
typedef unsigned short int uint16;

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

    bool getIsPlayerField();

    void updateSquareSize();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    QWidget *parent;

    ShipMk1 *shipMk1_1;
    ShipMk1 *shipMk1_2;
    ShipMk1 *shipMk1_3;
    ShipMk1 *shipMk1_4;
    ShipMk2 *shipMk2_1;
    ShipMk2 *shipMk2_2;
    ShipMk2 *shipMk2_3;
    ShipMk3 *shipMk3_1;
    ShipMk3 *shipMk3_2;
    ShipMk4 *shipMk4;

    uint squareSize;
    uint const squareCount = 10;

    static inline uint16 fieldCount = 0;
    bool isPlayerField;
};

#endif // FIELD_H
