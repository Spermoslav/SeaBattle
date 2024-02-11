#include "ships.h"

Ships::Ships(QWidget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
}

void Ships::resizeEvent(QResizeEvent *e)
{

}

ShipMk4::ShipMk4(QWidget *parent)
    : Ships(parent)
{

}

ShipMk3::ShipMk3(QWidget *parent)
    : Ships(parent)
{

}

ShipMk2::ShipMk2(QWidget *parent)
    : Ships(parent)
{

}

ShipMk1::ShipMk1(QWidget *parent)
    : Ships(parent)
{

}


