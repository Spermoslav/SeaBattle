#include "tools.h"
#include "widget.h"

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

    mainMenu = new MainMenu(parent);
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
    mainMenu->setGeometry(parent->width() / 3, parent->height() / 3, parent->width() / 3, parent->height() / 3);
}

void ToolsBar::mainMenuPBClicked()
{
    mainMenu->show();
    mainMenu->getToolsBarGShadow().show();
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
    parent->getFieldPlayer()->randomMoveAllShips();
}

void ToolsBar::botMotionPBClicked()
{
    if(parent->gameStart) bot->motion();
}

MainMenu::MainMenu(Widget *parent)
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

    exitGamePB = new QPushButton("exit", this);
    connect(exitGamePB, &QPushButton::clicked, this, &MainMenu::exitGamePBClicked);

    raise();
    hide();
    backgroundShadow->hide();
}

QWidget &MainMenu::getToolsBarGShadow() const
{
    return *backgroundShadow;
}

void MainMenu::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    backgroundShadow->setGeometry(0, 0, parent->width(), parent->height());
    closePB->setGeometry(width() * 0.8, 0, width() * 0.2, height() * 0.2);
    resetGamePB->setGeometry(width() * 0.1, height() * 0.5, width() * 0.8, height() * 0.1);
    exitGamePB->setGeometry(width() * 0.1, height() * 0.7, width() * 0.8, height() * 0.1);
}

void MainMenu::closePBClicked()
{
    hide();
    backgroundShadow->hide();
}

void MainMenu::resetGamePBClicked()
{
    parent->resetGame();
    closePBClicked();
}

void MainMenu::exitGamePBClicked()
{

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
    playerScoreLabel->setText("Ваши очки: " + QString::number(playerScore));
    playerDestroyShipsLabel->setText("Уничтожено кораблей соперника: " + QString::number(playerDestroyShips));
    botScoreLabel->setText("Очки бота: " + QString::number(botScore));
    botDestroyShipsLabel->setText("Уничтожено ваших кораблей: " + QString::number(botDestroyShips));
}

void InfoBar::reset()
{
    playerScore        = 0;
    playerDestroyShips = 0;
    botScore           = 0;
    botDestroyShips    = 0;
    updateLabels();
}

void InfoBar::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
}



