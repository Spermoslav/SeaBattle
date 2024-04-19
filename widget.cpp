#include "widget.h"
#include "ui_widget.h"
#include "field.h"
#include "ships.h"
#include "tools.h"
#include "bot.h"

Widget::Widget(QWidget *parent) noexcept
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMinimumSize(400, 400);
    gameIsStart = false;

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

void Widget::randomMovePlayerShips() noexcept
{
    if(!gameIsStart) fieldPlayer->randomMoveAllShips();
}

void Widget::updateWidgetsSize() noexcept
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

const BotField *Widget::getFieldBot() const noexcept
{
    return fieldBot;
}

const PlayerField *Widget::getFieldPlayer() const noexcept
{
    return fieldPlayer;
}

Bot *Widget::getBot() noexcept
{
    return bot;
}

void Widget::showMainMenu() noexcept
{
    mainMenu->show();
}

void Widget::resetGame() noexcept
{
    gameIsStart = false;
    bot->reset();
    toolsBar->reset();
    fieldPlayer->reset();
    fieldBot->reset();
    infoBar->reset();

}

bool Widget::startGame() noexcept
{
    if(!gameIsStart) {
        for(auto const &targetShip : fieldPlayer->getAllShips()) {
            for(auto const &ship : fieldPlayer->getAllShips()) {
                if(targetShip != ship){
                    if(targetShip->checkShipCollision(targetShip->pos(), ship)) {
                        return false;
                    }
                }
            }
        }
        fieldBot->randomMoveAllShips();
        gameIsStart = true;
        return true;
    }
    return false;
}

void Widget::finishGame(Winner win) noexcept
{
    winMenu->show(win);
    resetGame();
}

bool Widget::getGameIsStart() const noexcept
{
    return gameIsStart;
}

void Widget::resizeEvent(QResizeEvent *e) noexcept
{
    Q_UNUSED(e)
    updateWidgetsSize();
}

void Widget::mousePressEvent(QMouseEvent *e) noexcept
{
    Q_UNUSED(e)
}

void Widget::mouseMoveEvent(QMouseEvent *e) noexcept
{
    Q_UNUSED(e)
}

