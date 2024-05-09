#ifndef TOOLS_H
#define TOOLS_H

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include "game.h"

class ToolsBar : public QGroupBox
{
public:
    ToolsBar(Game *parent, Bot *bot) noexcept;

    void reset();

    const Game *getParent() const { return parent; }

    const static inline QString MAINMENU_PB_NAME   = "Главное меню";
    const static inline QString STARTGAME_PB_NAME  = "Начать игру";
    const static inline QString RANDOMMOVE_PB_NAME = "Разместить корабли в случайном порядке";
    const static inline QString BOTMOUTION_PB_NAME = "bot moution";

private slots:

    void resizeEvent(QResizeEvent *e) override;
    void mainMenuPBClicked();
    void startGamePBClicked();
    void randomMovePlayerShipsPBClicked();
    void botMotionPBClicked();

private:
    Game *parent;

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
    Menu(Game *parent) ;

    void hide();
    void resize();

    const static inline QString CLOSE_PB_NAME = "Закрыть";
    const static inline QString RESET_PB_NAME = "Перезагрузить игру";

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void closePBClicked();
    void resetGamePBClicked();

protected:
    virtual void placeObjects() = 0;

    Game *parent;

    QWidget *backgroundShadow;

    QPushButton *closePB;
    QPushButton *resetGamePB;
};

class MainMenu : public Menu
{
public:
    MainMenu(Game *parent);

    void show();

    const static inline QString EASY_RB_NAME   = "Легко";
    const static inline QString MEDIUM_RB_NAME = "Средне";
    const static inline QString HARD_RB_NAME   = "Тяжело";
    const static inline QString DIFFLABEL_TEXT = "Сложность";

private slots:
    void easyRBClicked();
    void mediumRBClicked();
    void hardRBClicked();

private:
    void placeObjects() override;

    QRadioButton *easyRB;
    QRadioButton *mediumRB;
    QRadioButton *hardRB;
    QLabel *diffLabel;
    QGridLayout *diffLay;
};

class WinMenu : public Menu
{
public:

    WinMenu(Game *parent);

    void show(Gamer winner);

    const static inline QString PLAYERWIN_TEXT = "Ты выйграл";
    const static inline QString BOTWIN_TEXT    = "Бот выйграл";

private:
    void setWinLabel(Gamer wr);
    void placeObjects() override;

    QLabel *winLabel;
};

class InfoBar : public QGroupBox
{
public:
    InfoBar(Game *parent) noexcept;

    void updateLabels();

    void reset();

    void playerScoreAdd();
    void playerDestroyShipsAdd();
    void botScoreAdd();
    void botDestroyShipsAdd();

    const Game *getParent() const { return parent; }

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
        const QString hideBG  = "background-color: rgba(0, 0, 0, 0);";
    private slots:
        void resizeEvent(QResizeEvent *e) override;
    private:
        InfoBar *parent;
    };
    Hint *hint;
private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    Game *parent;

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
