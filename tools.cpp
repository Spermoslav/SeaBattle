#include "tools.h"
#include "field.h"
#include "bot.h"

ToolsBar::ToolsBar(Widget *parent)
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

Widget *ToolsBar::getParent() const
{
    return parent;
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
    for(auto const &targetShip : parent->getFieldPlayer()->getAllShips()) {
        for(auto const &ship : parent->getFieldPlayer()->getAllShips()) {
            if(targetShip != ship){
                if(targetShip->checkShipCollision(targetShip->pos(), ship)) {
                    return;
                }
            }
        }
    }
    parent->getFieldBot()->randomMoveAllShips();
    parent->gameStart = true;
    startGamePB->setDisabled(true);
}

void ToolsBar::randomMovePlayerShipsPBClicked()
{
    if(!parent->gameStart) parent->getFieldPlayer()->randomMoveAllShips();
}

void ToolsBar::botMotionPBClicked()
{
    if(parent->gameStart) bot->motion();
}




InfoBar::InfoBar(QWidget *parent)
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

Menu::Menu(Widget *parent)
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


MainMenu::MainMenu(Widget *parent)
    : Menu(parent)
{

}

void MainMenu::show()
{
    static_cast<QGroupBox*> (this)->show();
    backgroundShadow->show();
}

void MainMenu::placeObjects()
{
    backgroundShadow->setGeometry(0, 0, parent->width(), parent->height());
    closePB->setGeometry(width() * 0.8, 0, width() * 0.2, height() * 0.2);
    resetGamePB->setGeometry(width() * 0.1, height() * 0.5, width() * 0.8, height() * 0.1);
}

WinMenu::WinMenu(Widget *parent)
    : Menu(parent)
{
    winLabel = new QLabel(this);
    winLabel->setAlignment(Qt::AlignCenter);
    winLabel->setFont(QFont(winLabel->font().family(), 15));
    winLabel->setStyleSheet("border: 0px;");
}

void WinMenu::show(Winner wr)
{
    setWinLabel(wr);
    static_cast<QGroupBox*> (this)->show();
    backgroundShadow->show();
}

void WinMenu::setWinLabel(Winner wr)
{
    if (wr == Winner::player) winLabel->setText(playerWinStr);
    else                      winLabel->setText(botWinStr);
}

void WinMenu::placeObjects()
{
    backgroundShadow->setGeometry(0, 0, parent->width(), parent->height());
    closePB->setGeometry(width() * 0.8, 0, width() * 0.2, height() * 0.2);
    winLabel->setGeometry(width() * 0.1, height() * 0.25, width() * 0.8, height() * 0.2);
    resetGamePB->setGeometry(width() * 0.1, height() * 0.5, width() * 0.8, height() * 0.1);
}
