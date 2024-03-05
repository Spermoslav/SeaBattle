#ifndef TOOLS_H
#define TOOLS_H

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>

class MainMenu;

class ToolsBar : public QGroupBox
{
public:
    ToolsBar(QWidget *parent);

private slots:

    void resizeEvent(QResizeEvent *e) override;

private:
    QWidget *parent;

    QPushButton *mainMenuPB;
};


class MainMenu
{
public:

private:

};

#endif // TOOLS_H
