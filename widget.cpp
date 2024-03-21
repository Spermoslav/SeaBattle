#include "widget.h"
#include "ui_widget.h"

#include <algorithm>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    fieldPlayer = new Field(this);
    fieldBot = new Field(this);

    tb = new ToolsBar(this);
    fieldBot->updateSquareSize();
    fieldPlayer->updateSquareSize();
    int fieldSize = fieldPlayer->getSquareSize() * fieldPlayer->getSquareCount();
    fieldBot->setGeometry(0, 0, fieldSize, fieldSize);
    fieldPlayer->setGeometry(0, fieldSize, fieldSize, fieldSize);

    tb->setGeometry(fieldSize, 0, width() - fieldSize, height());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    fieldBot->updateSquareSize();
    fieldPlayer->updateSquareSize();
    int fieldSize = fieldPlayer->getSquareSize() * fieldPlayer->getSquareCount();
    fieldBot->setGeometry(0, 0, fieldSize, fieldSize);
    fieldPlayer->setGeometry(0, fieldSize, fieldSize, fieldSize);
    tb->setGeometry(fieldSize, 0, width() - fieldSize, height());
}

void Widget::mousePressEvent(QMouseEvent *e)
{

}

void Widget::mouseMoveEvent(QMouseEvent *e)
{

}

