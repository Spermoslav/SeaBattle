#ifndef TOOLS_H
#define TOOLS_H

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

class MainMenu;
class Widget;
class Ship;
class Bot;

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

    MainMenu *mainMenu;
};

//class Menu : public QGroupBox
//{
//public:
//    Menu(Widget *parent);

//    QWidget &getToolsBarGShadow() const;

//private slots:
//    void resizeEvent(QResizeEvent *e) override;
//    void closePBClicked();
//    void resetGamePBClicked();
//    void exitGamePBClicked();

//private:
//    Widget *parent;

//    QWidget *backgroundShadow;

//    QPushButton *closePB;
//    QPushButton *resetGamePB;
//    QPushButton *exitGamePB;
//};

class MainMenu : public QGroupBox
{
public:
    MainMenu(Widget *parent);

    QWidget &getToolsBarGShadow() const;

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void closePBClicked();
    void resetGamePBClicked();
    void exitGamePBClicked();

private:
    Widget *parent;

    QWidget *backgroundShadow;

    QPushButton *closePB;
    QPushButton *resetGamePB;
    QPushButton *exitGamePB;
};

class InfoBar : public QGroupBox
{
public:
    InfoBar(QWidget *parent);

    void updateLabels();

    void reset();

private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    QWidget *parent;

    QLabel *playerScoreLabel;
    QLabel *playerDestroyShipsLabel;
    QLabel *botScoreLabel;
    QLabel *botDestroyShipsLabel;

    QGridLayout *labelsLay;
public:
    quint16 playerScore        = 0;
    quint16 playerDestroyShips = 0;
    quint16 botScore           = 0;
    quint16 botDestroyShips    = 0;
};

//class WinMenu : public QGroupBox
//{
//public:

//    WinMenu(Widget *parent);

//    const static QString playerWinStr;
//    const static QString botWinStr;

//private:
//    Widget *parent;

//    QLabel *winLabel;
//    QPushButton *
//};

#endif // TOOLS_H
