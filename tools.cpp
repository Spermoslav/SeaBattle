#include "tools.h"
#include "field.h"
#include "bot.h"

ToolsBar::ToolsBar(Widget *parent) noexcept
    : QGroupBox(parent)
{
    this->parent = parent;
    bot = parent->getBot();

    setStyleSheet("border: 1px solid black");

    mainMenuPB = new QPushButton;
    mainMenuPB->setText("Main Menu");
    connect(mainMenuPB, &QPushButton::clicked, this, &ToolsBar::mainMenuPBClicked);

    startGamePB = new QPushButton;
    startGamePB->setText("start game");
    connect(startGamePB, &QPushButton::clicked, this, &ToolsBar::startGamePBClicked);

    randomMovePlayerShipsPB = new QPushButton;
    randomMovePlayerShipsPB->setText("random move");
    connect(randomMovePlayerShipsPB, &QPushButton::clicked, this, &ToolsBar::randomMovePlayerShipsPBClicked);

    botMotionPB = new QPushButton;
    botMotionPB->setText("botMotion");
    connect(botMotionPB, &QPushButton::clicked, this, &ToolsBar::botMotionPBClicked);

    toolsVBoxLayout = new QVBoxLayout(this);
    toolsVBoxLayout->addWidget(mainMenuPB);
    toolsVBoxLayout->addWidget(startGamePB);
    toolsVBoxLayout->addWidget(randomMovePlayerShipsPB);
    toolsVBoxLayout->addWidget(botMotionPB);
}

const Widget *ToolsBar::getParent() const noexcept
{
    return parent;
}

void ToolsBar::reset() noexcept
{
    startGamePB->setDisabled(false);
}

void ToolsBar::resizeEvent(QResizeEvent *e) noexcept
{
    Q_UNUSED(e)
}

void ToolsBar::mainMenuPBClicked() noexcept
{
    parent->showMainMenu();
}

void ToolsBar::startGamePBClicked() noexcept
{
    startGamePB->setDisabled(parent->startGame());
}

void ToolsBar::randomMovePlayerShipsPBClicked() noexcept
{
    if(!parent->getGameIsStart()) parent->randomMovePlayerShips();
}

void ToolsBar::botMotionPBClicked() noexcept
{
    if(parent->getGameIsStart()) bot->motion();
}


InfoBar::InfoBar(QWidget *parent) noexcept
    : QGroupBox(parent)
{
    this->parent = parent;
    setStyleSheet("border: 1px solid black;");

    playerScoreLabel        = new QLabel;
    playerDestroyShipsLabel = new QLabel;
    botScoreLabel           = new QLabel;
    botDestroyShipsLabel    = new QLabel;

    labelsLay = new QGridLayout(this);
    labelsLay->addWidget(playerScoreLabel, 1, 0);
    labelsLay->addWidget(playerDestroyShipsLabel, 1, 1);
    labelsLay->addWidget(botScoreLabel, 0, 0);
    labelsLay->addWidget(botDestroyShipsLabel, 0, 1);

    updateLabels();
}

void InfoBar::updateLabels() noexcept
{
    playerScoreLabel->setText(playerScoreStr + QString::number(playerScore));
    playerDestroyShipsLabel->setText(playerDestroyShipsStr + QString::number(playerDestroyShips));
    botScoreLabel->setText(botScoreStr + QString::number(botScore));
    botDestroyShipsLabel->setText(botDestroyShipsStr + QString::number(botDestroyShips));
}

void InfoBar::reset() noexcept
{
    playerScore        = 0;
    playerDestroyShips = 0;
    botScore           = 0;
    botDestroyShips    = 0;
    updateLabels();
}

void InfoBar::playerScoreAdd() noexcept
{
    playerScoreLabel->setText(playerScoreStr + QString::number(++playerScore));
}

void InfoBar::playerDestroyShipsAdd() noexcept
{
    playerDestroyShipsLabel->setText(playerDestroyShipsStr + QString::number(++playerDestroyShips));
}

void InfoBar::botScoreAdd() noexcept
{
    botScoreLabel->setText(botScoreStr + QString::number(++botScore));
}

void InfoBar::botDestroyShipsAdd() noexcept
{
    botDestroyShipsLabel->setText(botDestroyShipsStr + QString::number(++botDestroyShips));
}

void InfoBar::resizeEvent(QResizeEvent *e) noexcept
{
    Q_UNUSED(e)
}

Menu::Menu(Widget *parent) noexcept
    : QGroupBox(parent)
{
    this->parent = parent;
    setStyleSheet("border: 1px solid black;"
                  "background-color: white;");

    backgroundShadow = new QWidget(parent);
    backgroundShadow->setStyleSheet("background-color: rgba(0, 0, 0, 130);");

    closePB = new QPushButton("close", this);
    connect(closePB, &QPushButton::clicked, this, &MainMenu::closePBClicked);

    resetGamePB = new QPushButton("reset", this);
    connect(resetGamePB, &QPushButton::clicked, this, &MainMenu::resetGamePBClicked);

    raise();
    hide();
}

void Menu::hide() noexcept
{
    static_cast<QGroupBox*> (this)->hide();
    backgroundShadow->hide();
}

void Menu::resize() noexcept
{
    setGeometry(parent->width() / 3, parent->height() / 3, parent->width() / 3, parent->height() / 3);
}

void Menu::resizeEvent(QResizeEvent *e) noexcept
{
    Q_UNUSED(e)
    placeObjects();
}

void Menu::closePBClicked() noexcept
{
    hide();
}

void Menu::resetGamePBClicked() noexcept
{
    parent->resetGame();
    hide();
}


void MainMenu::show() noexcept
{
    static_cast<QGroupBox*> (this)->show();
    backgroundShadow->show();
}

void MainMenu::placeObjects() noexcept
{
    backgroundShadow->setGeometry(0, 0, parent->width(), parent->height());
    closePB->setGeometry(width() * 0.8, 0, width() * 0.2, height() * 0.2);
    resetGamePB->setGeometry(width() * 0.1, height() * 0.5, width() * 0.8, height() * 0.1);
}


WinMenu::WinMenu(Widget *parent) noexcept
    : Menu(parent)
{
    winLabel = new QLabel(this);
    winLabel->setAlignment(Qt::AlignCenter);
    winLabel->setFont(QFont(winLabel->font().family(), 15));
    winLabel->setStyleSheet("border: 0px;");
}

void WinMenu::show(Winner wr) noexcept
{
    setWinLabel(wr);
    static_cast<QGroupBox*> (this)->show();
    backgroundShadow->show();
}

void WinMenu::setWinLabel(Winner wr) noexcept
{
    if (wr == Winner::player) winLabel->setText(playerWinStr);
    else                      winLabel->setText(botWinStr);
}

void WinMenu::placeObjects() noexcept
{
    backgroundShadow->setGeometry(0, 0, parent->width(), parent->height());
    closePB->setGeometry(width() * 0.8, 0, width() * 0.2, height() * 0.2);
    winLabel->setGeometry(width() * 0.1, height() * 0.25, width() * 0.8, height() * 0.2);
    resetGamePB->setGeometry(width() * 0.1, height() * 0.5, width() * 0.8, height() * 0.1);
}
