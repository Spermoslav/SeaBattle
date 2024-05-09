#ifndef GAME_H
#define GAME_H

//#define DEBUG

#ifdef DEBUG
    #define GAME_QUEUEMOVE_LOCK
    #define BOT_SHIPS_SHOW
    #define BOT_UNMISS_FIRSTHIT
    #define BOT_TIMER_LOCK
    #define TOOLS_PB_BOTMOTION_SHOW
#endif // DEBUG

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Field;
class PlayerField;
class BotField;
class Ship;
class PlayerShip;
class BotShip;
class Damage;
class ToolsBar;
class InfoBar;
class MainMenu;
class WinMenu;
class Bot;

enum class Difficult
{
    easy,
    medium,
    hard
};

enum class Gamer {
    bot,
    player
};

enum GameStatus {
    finished,
    started,
    over
};

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr) noexcept;
    ~Game();

    void randomMovePlayerShips();
    void updateWidgetsSize();
    void showMainMenu();
    void changeWhoMove();
    void resetGame();
    bool startGame();
    void finishGame(Gamer winner);
    void activateBot();
    void changeDifficult(Difficult diff);

    Gamer      getWhoMove()    const { return whoMove;    }
    GameStatus getGameStatus() const { return gameStatus; }

    const Bot *getBot() const { return bot; }
    const BotField *getFieldBot() const { return fieldBot; }
    const PlayerField *getFieldPlayer() const { return fieldPlayer; }

    InfoBar *infoBar;

private slots:
    void resizeEvent(QResizeEvent *e)     override;
    void mousePressEvent(QMouseEvent *e)  override;
    void mouseMoveEvent(QMouseEvent *e)   override;

private:
    Ui::Game *ui;

    PlayerField *fieldPlayer;
    BotField *fieldBot;

    ToolsBar *toolsBar;

    Bot *bot;

    MainMenu *mainMenu;
    WinMenu *winMenu;

    Gamer whoMove;

    GameStatus gameStatus = finished;
};
#endif // GAME_H
