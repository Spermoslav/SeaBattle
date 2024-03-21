#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPainter>

typedef unsigned int uint;
typedef unsigned short int uint16;

class Ship;
class ShipMk4;
class ShipMk3;
class ShipMk2;
class ShipMk1;


class Field : public QGroupBox
{
    Q_OBJECT
public:
    Field(QWidget *parent);

    int getSquareSize() const;
    uint getSquareCount() const;

    bool getIsPlayerField();

    void updateSquareSize();

    void randomMoveAllShips();

    std::vector<Ship*> getAllShips();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    QWidget *parent;

    std::vector<Ship*> allShips;

    int squareSize;
    uint const squareCount = 10;

    static inline uint16 fieldCount = 0;
    bool isPlayerField;
};

#endif // FIELD_H
