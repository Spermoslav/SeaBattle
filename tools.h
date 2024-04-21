#ifndef TOOLS_H
#define TOOLS_H

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include "widget.h"


class ToolsBar : public QGroupBox
{
public:
    ToolsBar(Widget *parent) noexcept;

    void reset() noexcept;

    const Widget *getParent() const noexcept;

private slots:

    void resizeEvent(QResizeEvent *e) noexcept override;
    void mainMenuPBClicked()  noexcept;
    void startGamePBClicked() noexcept;
    void randomMovePlayerShipsPBClicked() noexcept;
    void botMotionPBClicked() noexcept;

private:
    Widget *parent;

    QPushButton *mainMenuPB;
    QPushButton *startGamePB;
    QPushButton *randomMovePlayerShipsPB;
    QPushButton *botMotionPB;

    Bot *bot;

    QVBoxLayout *toolsVBoxLayout;
};

class Menu : public QGroupBox
{
public:
    Menu(Widget *parent) noexcept;

    void hide()   noexcept;
    void resize() noexcept;

private slots:
    void resizeEvent(QResizeEvent *e) noexcept override;
    void closePBClicked()     noexcept;
    void resetGamePBClicked() noexcept;

protected:
    virtual void placeObjects() noexcept = 0;

    Widget *parent;

    QWidget *backgroundShadow;

    QPushButton *closePB;
    QPushButton *resetGamePB;
};

class MainMenu : public Menu
{
public:
    MainMenu(Widget *parent) : Menu(parent) {}

    void show() noexcept;

private:
    void placeObjects() noexcept override;
};

class WinMenu : public Menu
{
public:

    WinMenu(Widget *parent) noexcept;

    void show(Gamer winner) noexcept;

private:
    void setWinLabel(Gamer wr) noexcept;
    void placeObjects() noexcept override;

    QLabel *winLabel;

    const QString playerWinStr = "Ты выйграл";
    const QString botWinStr    = "Бот выйграл";
};

class InfoBar : public QGroupBox
{
public:
    InfoBar(QWidget *parent) noexcept;

    void updateLabels() noexcept;

    void reset() noexcept;

    void playerScoreAdd()        noexcept;
    void playerDestroyShipsAdd() noexcept;
    void botScoreAdd()        noexcept;
    void botDestroyShipsAdd() noexcept;

private slots:
    void resizeEvent(QResizeEvent *e) noexcept override;

private:
    QWidget *parent;

    QLabel *playerScoreLabel;
    QLabel *playerDestroyShipsLabel;
    QLabel *botScoreLabel;
    QLabel *botDestroyShipsLabel;

    QGridLayout *labelsLay;

    const QString playerScoreStr        = "Ваши очки: ";
    const QString playerDestroyShipsStr = "Уничтожено кораблей бота: ";
    const QString botScoreStr           = "Очки бота: ";
    const QString botDestroyShipsStr    = "Уничтожено ваших кораблей: ";

    quint8 playerScore         = 0;
    quint8 playerDestroyShips  = 0;
    quint8 botScore            = 0;
    quint8 botDestroyShips     = 0;
};

#endif // TOOLS_H
