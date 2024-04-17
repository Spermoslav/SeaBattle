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
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void updateWidgetsSize();

    InfoBar *getInfoBar();

    BotField *getFieldBot() const;
    PlayerField *getFieldPlayer() const;

    Bot *getBot();

    void showMainMenu();
    void resetGame();
    void finishGame(Winner win);

    bool gameStart;

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    Ui::Widget *ui;

    PlayerField *fieldPlayer;
    BotField *fieldBot;

    ToolsBar *toolsBar;

    InfoBar *infoBar;

    Bot *bot;

    MainMenu *mainMenu;
    WinMenu *winMenu;
};
#endif // WIDGET_H
