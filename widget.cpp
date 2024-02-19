#include "widget.h"
#include "ui_widget.h"

#include <algorithm>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    field = new Field(this);

    mk = new ShipMk3(field, field);
    mk2 = new ShipMk2(field, field);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    field->updateSquareSize();
    field->setGeometry(0, 0,
                field->getSquareSize() * field->getSquareCount(),field->getSquareSize() * field->getSquareCount());
    mk->resize();
    mk2->resize();
}

void Widget::mousePressEvent(QMouseEvent *e)
{

}

void Widget::mouseMoveEvent(QMouseEvent *e)
{

}

