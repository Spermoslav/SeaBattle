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

    whoMove = Gamer::player;

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
    if(gameStatus == finished) fieldPlayer->randomMoveAllShips();
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

void Widget::showMainMenu() noexcept
{
    mainMenu->show();
}

void Widget::changeWhoMove()
{
    if(whoMove == Gamer::bot) whoMove = Gamer::player;
    else whoMove = Gamer::bot;
}

void Widget::resetGame() noexcept
{
    gameStatus = finished;
    bot->reset();
    toolsBar->reset();
    fieldPlayer->reset();
    fieldBot->reset();
    infoBar->reset();
    whoMove = Gamer::player;
}

bool Widget::startGame() noexcept
{
    if(gameStatus == finished) {
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
        gameStatus = started;
        bot->activate();
        return true;
    }
    return false;
}

void Widget::finishGame(Gamer winner) noexcept
{
    winMenu->show(winner);
    bot->reset();
    gameStatus = over;
}

Gamer Widget::getWhoMove() const
{
    return whoMove;
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

