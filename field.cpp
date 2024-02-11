#include "field.h"

Field::Field(QWidget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
}

void Field::resizeEvent(QResizeEvent *e)
{
    setGeometry(parent->width() * 0.01, parent->height() * 0.01, parent->width() * 0.98, parent->height() * 0.98);
}
