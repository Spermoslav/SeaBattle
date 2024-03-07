#include "field.h"
#include "ships.h"

#include <algorithm>

Field::Field(QWidget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
    fieldCount++;
    if(fieldCount == 1) isPlayerField = true;
    else isPlayerField = false;

    updateSquareSize();

    shipMk1_1 = new ShipMk1(this);
    shipMk1_2 = new ShipMk1(this);
    shipMk1_3 = new ShipMk1(this);
    shipMk1_4 = new ShipMk1(this);
    shipMk2_1 = new ShipMk2(this);
    shipMk2_2 = new ShipMk2(this);
    shipMk2_3 = new ShipMk2(this);
    shipMk3_1 = new ShipMk3(this);
    shipMk3_2 = new ShipMk3(this);
    shipMk4 = new ShipMk4(this);

}

int Field::getSquareSize()
{
    return squareSize;
}

uint Field::getSquareCount()
{
    return squareCount;
}

bool Field::getIsPlayerField()
{
    return isPlayerField;
}

void Field::updateSquareSize()
{
    squareSize = std::min(parent->width() / 2, parent->height() / 2) / squareCount;
}

void Field::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    repaint();
    shipMk1_1->resize();
    shipMk1_2->resize();
    shipMk1_3->resize();
    shipMk1_4->resize();
    shipMk2_1->resize();
    shipMk2_2->resize();
    shipMk2_3->resize();
    shipMk3_1->resize();
    shipMk3_2->resize();
    shipMk4->resize();
}

void Field::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p;
    p.begin(this);
    p.drawRect(0, 0, width() - 2, height() - 2);
    for(uint i = 0; i < squareCount; i++) {
        for(uint j = 0; j < squareCount; j++) {
            p.drawRect(i * squareSize, j * squareSize, squareSize, squareSize);
        }
    }
    p.end();
}
