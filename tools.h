#ifndef TOOLS_H
#define TOOLS_H

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainMenu;

class ToolsBar : public QGroupBox
{
public:
    ToolsBar(QWidget *parent);

private slots:

    void resizeEvent(QResizeEvent *e) override;
    void mainMenuPBClicked();
    void startGamePBClicked();

private:
    QWidget *parent;

    QPushButton *mainMenuPB;
    QPushButton *startGamePB;

    QVBoxLayout *toolsVBoxLayout;

    MainMenu *mainMenu;
};


class MainMenu : public QGroupBox
{
public:
    MainMenu(QWidget *parent);

    QWidget &getBGShadow();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void closePBClicked();
    void resetGamePBClicked();
    void exitGamePBClicked();

private:
    QWidget *parent;

    QWidget *backgroundShadow;

    QPushButton *closePB;
    QPushButton *resetGamePB;
    QPushButton *exitGamePB;
};

#endif // TOOLS_H
