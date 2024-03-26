#include "widget.h"
#include "ui_widget.h"
#include <thread>
#include <algorithm>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    check = false;
    gameStart = false;
    infoBar = new InfoBar(this);

    fieldPlayer = new Field(this);
    fieldPlayer->spawnShips();
    fieldBot = new Field(this);
    fieldBot->spawnShips();
    toolsBar = new ToolsBar(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateWidgetsSize()
{

    infoBar->resize(width() , height() * 0.1);
    const int fieldSize = std::min(width() / 2, (height() - infoBar->height()) / 2);
    fieldBot->reSize();
    fieldPlayer->reSize();
    infoBar->move(0, fieldSize);
    fieldPlayer->move(0, infoBar->y() + infoBar->height());
    toolsBar->setGeometry(fieldBot->width(), 0, width() - fieldBot->width(), height());
    infoBar->resize(width() - toolsBar->width(), height() * 0.1);
}

InfoBar &Widget::getInfoBar() const
{
    return *infoBar;
}

Field &Widget::getFieldBot() const
{
    return *fieldBot;
}

Field &Widget::getFieldPlayer() const
{
    return *fieldPlayer;
}

void Widget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    updateWidgetsSize();
}

void Widget::mousePressEvent(QMouseEvent *e)
{

}

void Widget::mouseMoveEvent(QMouseEvent *e)
{

}

