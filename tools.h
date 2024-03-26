#ifndef TOOLS_H
#define TOOLS_H

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainMenu;
class Widget;
class Ships;

class ToolsBar : public QGroupBox
{
public:
    ToolsBar(Widget *parent);

private slots:

    void resizeEvent(QResizeEvent *e) override;
    void mainMenuPBClicked();
    void startGamePBClicked();
    void randomMovePlayerShipsPBClicked();

private:
    Widget *parent;

    QPushButton *mainMenuPB;
    QPushButton *startGamePB;
    QPushButton *randomMovePlayerShipsPB;

    QVBoxLayout *toolsVBoxLayout;

    MainMenu *mainMenu;
};


class MainMenu : public QGroupBox
{
public:
    MainMenu(QWidget *parent);

    QWidget &getToolsBarGShadow() const;

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

class InfoBar : public QGroupBox
{
public:
    InfoBar(QWidget *parent);

private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    QWidget *parent;
};



#endif // TOOLS_H
