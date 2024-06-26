#include "tools.h"
#include "field.h"
#include "bot.h"

ToolsBar::ToolsBar(Game *parent, Bot *bot) noexcept
    : QGroupBox(parent)
{
    this->parent = parent;
    this->bot = bot;

    setStyleSheet("border: 1px solid black");

    mainMenuPB = new QPushButton;
    mainMenuPB->setText(MAINMENU_PB_NAME);
    connect(mainMenuPB, &QPushButton::clicked, this, &ToolsBar::mainMenuPBClicked);

    startGamePB = new QPushButton;
    startGamePB->setText(STARTGAME_PB_NAME);
    connect(startGamePB, &QPushButton::clicked, this, &ToolsBar::startGamePBClicked);

    randomMovePlayerShipsPB = new QPushButton;
    randomMovePlayerShipsPB->setText(RANDOMMOVE_PB_NAME);
    connect(randomMovePlayerShipsPB, &QPushButton::clicked, this, &ToolsBar::randomMovePlayerShipsPBClicked);

    botMotionPB = new QPushButton;
    botMotionPB->setText(BOTMOUTION_PB_NAME);
    connect(botMotionPB, &QPushButton::clicked, this, &ToolsBar::botMotionPBClicked);

    toolsVBoxLayout = new QVBoxLayout(this);
    toolsVBoxLayout->addWidget(mainMenuPB);
    toolsVBoxLayout->addWidget(startGamePB);
    toolsVBoxLayout->addWidget(randomMovePlayerShipsPB);
    toolsVBoxLayout->addWidget(botMotionPB);

#ifndef TOOLS_PB_BOTMOTION_SHOW
    botMotionPB->hide();
#endif
}

void ToolsBar::reset()
{
    startGamePB->setDisabled(false);
}

void ToolsBar::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
}

void ToolsBar::mainMenuPBClicked()
{
    parent->showMainMenu();
}

void ToolsBar::startGamePBClicked()
{
    startGamePB->setDisabled(parent->startGame());
}

void ToolsBar::randomMovePlayerShipsPBClicked()
{
    if(parent->getGameStatus() == finished) parent->randomMovePlayerShips();
}

void ToolsBar::botMotionPBClicked()
{
    if(parent->getGameStatus() == started) bot->motion();
}


InfoBar::InfoBar(Game *parent) noexcept
    : QGroupBox(parent)
{
    this->parent = parent;
    setStyleSheet("border: 1px solid black;");

    playerScoreLabel        = new QLabel;
    playerDestroyShipsLabel = new QLabel;
    botScoreLabel           = new QLabel;
    botDestroyShipsLabel    = new QLabel;

    hint = new Hint(this);


    scoreLabelsLay = new QGridLayout;
    scoreLabelsLay->addWidget(playerScoreLabel, 1, 0);
    scoreLabelsLay->addWidget(playerDestroyShipsLabel, 1, 1);
    scoreLabelsLay->addWidget(botScoreLabel, 0, 0);
    scoreLabelsLay->addWidget(botDestroyShipsLabel, 0, 1);

    labelsLay = new QVBoxLayout(this);
    labelsLay->addLayout(scoreLabelsLay);
    labelsLay->addWidget(hint);

    updateLabels();
}

void InfoBar::updateLabels()
{
    playerScoreLabel->setText(playerScoreStr + QString::number(playerScore));
    playerDestroyShipsLabel->setText(playerDestroyShipsStr + QString::number(playerDestroyShips));
    botScoreLabel->setText(botScoreStr + QString::number(botScore));
    botDestroyShipsLabel->setText(botDestroyShipsStr + QString::number(botDestroyShips));
}

void InfoBar::reset()
{
    playerScore        = 0;
    playerDestroyShips = 0;
    botScore           = 0;
    botDestroyShips    = 0;
    hint->reset();
    updateLabels();
}

void InfoBar::playerScoreAdd()
{
    playerScoreLabel->setText(playerScoreStr + QString::number(++playerScore));
}

void InfoBar::playerDestroyShipsAdd()
{
    playerDestroyShipsLabel->setText(playerDestroyShipsStr + QString::number(++playerDestroyShips));
}

void InfoBar::botScoreAdd()
{
    botScoreLabel->setText(botScoreStr + QString::number(++botScore));
}

void InfoBar::botDestroyShipsAdd()
{
    botDestroyShipsLabel->setText(botDestroyShipsStr + QString::number(++botDestroyShips));
}

void InfoBar::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
}

InfoBar::Hint::Hint(InfoBar *ib)
    : QLabel(ib)
{
    parent = ib;
    setAlignment(Qt::AlignCenter);
    setMaximumHeight(40);
}

void InfoBar::Hint::gameStartFault()
{
    setText(gameStartFaultStr);
    setStyleSheet(redBG);
    updateFontSize();
}

void InfoBar::Hint::gameStarted()
{
    updateWhoMove();
    updateFontSize();
}

void InfoBar::Hint::gameOver(Gamer win)
{
    if(win == Gamer::player) {
        setText(WinMenu::PLAYERWIN_TEXT);
        setStyleSheet(greenBG);
    }
    else {
        setText(WinMenu::BOTWIN_TEXT);
        setStyleSheet(redBG);
    }
}

void InfoBar::Hint::updateWhoMove()
{
    if(parent->getParent()->getWhoMove() == Gamer::player) {
        setText(playerMoveStr);
        setStyleSheet(greenBG);
    }
    else {
        setText(botMoveStr);
        setStyleSheet(redBG);
    }
}

void InfoBar::Hint::updateFontSize()
{
    if(text().size() > 20) setFont(QFont(font().family(), width() / text().size()));
    else if (text().size() > 0) setFont(QFont(font().family(), height() / 2));
    else setFont(QFont(font().family(), 20));
}

void InfoBar::Hint::reset()
{
    setStyleSheet(hideBG);
    setText("");
}

void InfoBar::Hint::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    updateFontSize();
}

Menu::Menu(Game *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
    setStyleSheet("border: 1px solid black;"
                  "background-color: white;");

    backgroundShadow = new QWidget(parent);
    backgroundShadow->setStyleSheet("background-color: rgba(0, 0, 0, 130);");

    closePB = new QPushButton(CLOSE_PB_NAME, this);
    connect(closePB, &QPushButton::clicked, this, &MainMenu::closePBClicked);

    resetGamePB = new QPushButton(RESET_PB_NAME, this);
    connect(resetGamePB, &QPushButton::clicked, this, &MainMenu::resetGamePBClicked);

    raise();
    hide();
}

void Menu::hide()
{
    static_cast<QGroupBox*> (this)->hide();
    backgroundShadow->hide();
}

void Menu::resize()
{
    setGeometry(parent->width() / 3, parent->height() / 3, parent->width() / 3, parent->height() / 3);
}

void Menu::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    placeObjects();
}

void Menu::closePBClicked()
{
    hide();
}

void Menu::resetGamePBClicked()
{
    parent->resetGame();
    hide();
}


MainMenu::MainMenu(Game *parent)
    : Menu(parent)
{
    easyRB = new QRadioButton;
    easyRB->setText(EASY_RB_NAME);
    easyRB->click();
    connect(easyRB, &QRadioButton::clicked, this, &MainMenu::easyRBClicked);

    mediumRB = new QRadioButton;
    mediumRB->setText(MEDIUM_RB_NAME);
    connect(mediumRB, &QRadioButton::clicked, this, &MainMenu::mediumRBClicked);

    hardRB = new QRadioButton;
    hardRB->setText(HARD_RB_NAME);
    connect(hardRB, &QRadioButton::clicked, this, &MainMenu::hardRBClicked);

    diffLabel = new QLabel;
    diffLabel->setText(DIFFLABEL_TEXT);
    diffLabel->setAlignment(Qt::AlignCenter);
    diffLabel->setStyleSheet("border: 0px");
    diffLabel->setMinimumWidth(62);

    diffLay = new QGridLayout(this);
    diffLay->addWidget(diffLabel, 0, 1);
    diffLay->addWidget(easyRB, 1, 0);
    diffLay->addWidget(mediumRB, 1, 1);
    diffLay->addWidget(hardRB, 1, 2);
    diffLay->setContentsMargins(0, 0, 0, 0);
}

void MainMenu::show()
{
    static_cast<QGroupBox*> (this)->show();
    backgroundShadow->show();
}

void MainMenu::easyRBClicked()
{
    parent->changeDifficult(Difficult::easy);
}

void MainMenu::mediumRBClicked()
{
    parent->changeDifficult(Difficult::medium);
}

void MainMenu::hardRBClicked()
{
    parent->changeDifficult(Difficult::hard);
}

void MainMenu::placeObjects()
{
    backgroundShadow->setGeometry(0, 0, parent->width(), parent->height());
    closePB->setGeometry(width() * 0.8, 0, width() * 0.2, height() * 0.2);
    resetGamePB->setGeometry(width() * 0.1, height() * 0.5, width() * 0.8, height() * 0.1);
    diffLay->setGeometry(QRect(width() * 0.05, height() * 0.65, width() * 0.9, height() * 0.3));
}


WinMenu::WinMenu(Game *parent)
    : Menu(parent)
{
    winLabel = new QLabel(this);
    winLabel->setAlignment(Qt::AlignCenter);
    winLabel->setFont(QFont(winLabel->font().family(), 15));
    winLabel->setStyleSheet("border: 0px;");
}

void WinMenu::show(Gamer winner)
{
    setWinLabel(winner);
    static_cast<QGroupBox*> (this)->show();
    backgroundShadow->show();
}

void WinMenu::setWinLabel(Gamer wr)
{
    if (wr == Gamer::player) winLabel->setText(PLAYERWIN_TEXT);
    else winLabel->setText(BOTWIN_TEXT);
}

void WinMenu::placeObjects()
{
    backgroundShadow->setGeometry(0, 0, parent->width(), parent->height());
    closePB->setGeometry(width() * 0.8, 0, width() * 0.2, height() * 0.2);
    winLabel->setGeometry(width() * 0.1, height() * 0.25, width() * 0.8, height() * 0.2);
    resetGamePB->setGeometry(width() * 0.1, height() * 0.5, width() * 0.8, height() * 0.1);
}
