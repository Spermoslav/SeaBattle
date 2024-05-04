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
    ToolsBar(Widget *parent, Bot *bot) noexcept;

    void reset();

    const Widget *getParent() const { return parent; }

private slots:

    void resizeEvent(QResizeEvent *e) override;
    void mainMenuPBClicked();
    void startGamePBClicked();
    void randomMovePlayerShipsPBClicked();
    void botMotionPBClicked();

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
    Menu(Widget *parent) ;

    void hide();
    void resize();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void closePBClicked();
    void resetGamePBClicked();

protected:
    virtual void placeObjects() = 0;

    Widget *parent;

    QWidget *backgroundShadow;

    QPushButton *closePB;
    QPushButton *resetGamePB;
};

class MainMenu : public Menu
{
public:
    MainMenu(Widget *parent) : Menu(parent) {}

    void show();

private:
    void placeObjects() override;
};

class WinMenu : public Menu
{
public:

    WinMenu(Widget *parent);

    void show(Gamer winner);

    const static QString playerWinStr;
    const static QString botWinStr;

private:
    void setWinLabel(Gamer wr);
    void placeObjects() override;

    QLabel *winLabel;
};

class InfoBar : public QGroupBox
{
public:
    InfoBar(Widget *parent) noexcept;

    void updateLabels();

    void reset();

    void playerScoreAdd();
    void playerDestroyShipsAdd();
    void botScoreAdd();
    void botDestroyShipsAdd();

    const Widget *getParent() const { return parent; }

    struct Hint : private QLabel
    {
        friend InfoBar;
        Hint(InfoBar *ib);

        void gameStartFault();
        void gameStarted();
        void gameOver(Gamer win);
        void updateWhoMove();
        void updateFontSize();
        void reset();

        const QString playerMoveStr = "Твой ход";
        const QString botMoveStr    = "Ход бота";
        const QString gameStartFaultStr = "Корабли неверно размещены";

        const QString redBG   = "background-color: rgb(255, 0, 0);";
        const QString greenBG = "background-color: rgb(0, 255, 0);";
        const QString hideBG  = "background-color: rgb(0, 0, 0);";
    private slots:
        void resizeEvent(QResizeEvent *e) override;
    private:
        InfoBar *parent;
    };
    Hint *hint;
private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    Widget *parent;

    QLabel *playerScoreLabel;
    QLabel *playerDestroyShipsLabel;
    QLabel *botScoreLabel;
    QLabel *botDestroyShipsLabel;

    QGridLayout *scoreLabelsLay;
    QVBoxLayout *labelsLay;

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
