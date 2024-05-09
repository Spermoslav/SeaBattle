#include "game.h"
#include "ui_widget.h"
#include "field.h"
#include "ships.h"
#include "tools.h"
#include "bot.h"

Game::Game(QWidget *parent) noexcept
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    if(rand() % 2) whoMove = Gamer::player;
    else whoMove = Gamer::bot;

    infoBar = new InfoBar(this);

    fieldPlayer = new PlayerField(this);
    fieldPlayer->spawnShips();

    fieldBot = new BotField(this);
    fieldBot->spawnShips();

    bot = new Bot(this, fieldPlayer);

    toolsBar = new ToolsBar(this, bot);

    mainMenu = new MainMenu(this);
    winMenu = new WinMenu(this);
}

Game::~Game()
{
    delete ui;
}

void Game::randomMovePlayerShips()
{
    if(gameStatus == finished) fieldPlayer->randomMoveAllShips();
}

void Game::updateWidgetsSize()
{

    infoBar->resize(width() , height() * 0.15);

    const int fieldSize = std::min(width() / 2, (height() - infoBar->height()) / 2);

    fieldBot->reSize();
    fieldPlayer->reSize();
    infoBar->move(0, fieldSize);
    fieldPlayer->move(0, infoBar->y() + infoBar->height());
    toolsBar->setGeometry(fieldBot->width(), 0, width() - fieldBot->width(), height());
    infoBar->resize(width() - toolsBar->width(), height() * 0.15);

    mainMenu->resize();
    winMenu->resize();
}

void Game::showMainMenu()
{
    mainMenu->show();
}

void Game::changeWhoMove()
{
    if(whoMove == Gamer::bot) whoMove = Gamer::player;
    else whoMove = Gamer::bot;
    infoBar->hint->updateWhoMove();
}

void Game::resetGame()
{
    gameStatus = finished;
    bot->reset();
    toolsBar->reset();
    fieldPlayer->reset();
    fieldBot->reset();
    infoBar->reset();
    if(rand() % 2) whoMove = Gamer::player;
    else whoMove = Gamer::bot;
}

bool Game::startGame()
{
    if(gameStatus == finished) {
        for(auto const &targetShip : fieldPlayer->getAllShips()) {
            for(auto const &ship : fieldPlayer->getAllShips()) {
                if(targetShip != ship){
                    if(targetShip->checkCollision(targetShip->pos(), ship)) {
                        infoBar->hint->gameStartFault();
                        return false;
                    }
                }
            }
        }
        fieldBot->randomMoveAllShips();
        gameStatus = started;
        bot->activate();
        infoBar->hint->gameStarted();
        return true;
    }
    infoBar->hint->gameStartFault();
    return false;
}

void Game::finishGame(Gamer winner)
{
    winMenu->show(winner);
    bot->reset();
    gameStatus = over;
    infoBar->hint->gameOver(winner);
}

void Game::activateBot()
{
    bot->activate();
}

void Game::changeDifficult(Difficult diff)
{
    bot->changeDifficult(diff);
}

void Game::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    updateWidgetsSize();
}

void Game::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Game::mouseMoveEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

