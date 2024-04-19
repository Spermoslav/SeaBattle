#ifndef WIDGET_H
#define WIDGET_H

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

enum class Winner {
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
    void resetGame() noexcept;
    bool startGame() noexcept;
    void finishGame(Winner win) noexcept;

    bool getGameIsStart() const noexcept;
    const BotField *getFieldBot() const noexcept;
    const PlayerField *getFieldPlayer() const noexcept;

    Bot *getBot() noexcept;


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

    bool gameIsStart;
};
#endif // WIDGET_H
