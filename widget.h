#ifndef WIDGET_H
#define WIDGET_H

#define DEBUG

#ifdef DEBUG
    #define GAME_QUEUEMOVE_LOCK
//    #define BOT_UNMISS_FIRSTHIT
    #define BOT_TIMER_LOCK
#endif // DEBUG

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
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

enum class Gamer {
    bot,
    player
};

class Widget : public QWidget
{
    Q_OBJECT
    friend Bot;
public:
    Widget(QWidget *parent = nullptr) noexcept;
    ~Widget();

    void randomMovePlayerShips() noexcept;
    void updateWidgetsSize() noexcept;
    void showMainMenu() noexcept;
    void changeWhoMove();
    void resetGame() noexcept;
    bool startGame() noexcept;
    void finishGame(Gamer winner) noexcept;

    bool getGameIsStart() const noexcept { return gameIsStart; }
    const BotField *getFieldBot() const noexcept { return fieldBot; }
    const PlayerField *getFieldPlayer() const noexcept { return fieldPlayer;}

    Bot *getBot() noexcept { return bot; }

    Gamer getWhoMove() const;

    InfoBar *infoBar;

private slots:
    void resizeEvent(QResizeEvent *e)    noexcept override;
    void mousePressEvent(QMouseEvent *e) noexcept override;
    void mouseMoveEvent(QMouseEvent *e)  noexcept override;

private:
    Ui::Widget *ui;

    PlayerField *fieldPlayer;
    BotField *fieldBot;

    ToolsBar *toolsBar;

    Bot *bot;

    MainMenu *mainMenu;
    WinMenu *winMenu;

    Gamer whoMove;

    bool gameIsStart = false;
};
#endif // WIDGET_H
