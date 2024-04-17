#include "widget.h"
#include "ui_widget.h"
#include "field.h"
#include "ships.h"
#include "tools.h"
#include "bot.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMinimumSize(400, 400);
    gameStart = false;

    infoBar = new InfoBar(this);

    fieldPlayer = new PlayerField(this);
    fieldPlayer->spawnShips();

    fieldBot = new BotField(this);
    fieldBot->spawnShips();

    bot = new Bot(this);

    toolsBar = new ToolsBar(this);

    mainMenu = new MainMenu(this);
    winMenu = new WinMenu(this);
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

    mainMenu->resize();
    winMenu->resize();
}

InfoBar *Widget::getInfoBar()
{
    return infoBar;
}

BotField *Widget::getFieldBot() const
{
    return fieldBot;
}

PlayerField *Widget::getFieldPlayer() const
{
    return fieldPlayer;
}

Bot *Widget::getBot()
{
    return bot;
}

void Widget::showMainMenu()
{
    mainMenu->show();
}

void Widget::resetGame()
{
    gameStart = false;
    bot->reset();
    toolsBar->reset();
    fieldPlayer->reset();
    fieldBot->reset();
    infoBar->reset();

}

void Widget::finishGame(Winner win)
{
    winMenu->show(win);
    gameStart = false;
}

void Widget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    updateWidgetsSize();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

