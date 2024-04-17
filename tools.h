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
    ToolsBar(Widget *parent);

    Widget *getParent() const;

    void reset();

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
    Menu(Widget *parent);

    QWidget &getToolsBarGShadow() const;

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
    MainMenu(Widget *parent);

    void show();


private slots:

private:
    void placeObjects() override;

};

class WinMenu : public Menu
{
public:

    WinMenu(Widget *parent);

    void show(Winner wr);

private:
    void setWinLabel(Winner wr);
    void placeObjects() override;

    QLabel *winLabel;

    const QString playerWinStr = "Ты выйграл";
    const QString botWinStr    = "Бот выйграл";
};

class InfoBar : public QGroupBox
{
public:
    InfoBar(QWidget *parent);

    void updateLabels();

    void reset();

    void playerScoreAdd();
    void playerDestroyShipsAdd();
    void botScoreAdd();
    void botDestroyShipsAdd();

private slots:
    void resizeEvent(QResizeEvent *e) override;

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
