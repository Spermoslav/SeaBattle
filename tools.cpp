#include "tools.h"

ToolsBar::ToolsBar(QWidget *parent)
    : QGroupBox(parent)
{
    this->parent = parent;

    setStyleSheet("border: 1px solid black");

    mainMenuPB = new QPushButton;
    mainMenuPB->setText("Main Menu");
    connect(mainMenuPB, &QPushButton::clicked, this, &ToolsBar::mainMenuPBClicked);

    startGamePB = new QPushButton;
    startGamePB->setText("start game");
    connect(startGamePB, &QPushButton::clicked, this, &ToolsBar::startGamePBClicked);

    toolsVBoxLayout = new QVBoxLayout(this);
    toolsVBoxLayout->addWidget(mainMenuPB);
    toolsVBoxLayout->addWidget(startGamePB);

    mainMenu = new MainMenu(parent);
}

void ToolsBar::resizeEvent(QResizeEvent *e)
{
    mainMenu->setGeometry(parent->width() / 3, parent->height() / 3, parent->width() / 3, parent->height() / 3);
}

void ToolsBar::mainMenuPBClicked()
{
    mainMenu->show();
    mainMenu->getBGShadow().show();
}

void ToolsBar::startGamePBClicked()
{

}

MainMenu::MainMenu(QWidget *parent)
    : QGroupBox(parent)
{

    this->parent = parent;
    setStyleSheet("border: 1px solid black;"
                  "background-color: white;");

    backgroundShadow = new QWidget(parent);
    backgroundShadow->setStyleSheet("background-color: rgba(0, 0, 0, 130);");

    closePB = new QPushButton(this);
    closePB->setText("close");
    connect(closePB, &QPushButton::clicked, this, &MainMenu::closePBClicked);

    resetGamePB = new QPushButton("reset", this);
    connect(resetGamePB, &QPushButton::clicked, this, &MainMenu::resetGamePBClicked);

    exitGamePB = new QPushButton("exit", this);
    connect(exitGamePB, &QPushButton::clicked, this, &MainMenu::exitGamePBClicked);

    raise();
    hide();
    backgroundShadow->hide();
}

QWidget &MainMenu::getBGShadow()
{
    return *backgroundShadow;
}

void MainMenu::resizeEvent(QResizeEvent *e)
{
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

}

void MainMenu::exitGamePBClicked()
{

}
