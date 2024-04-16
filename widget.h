#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>

#include "field.h"
#include "tools.h"
#include "ships.h"
#include "bot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum class Winner {
    bot,
    player
};

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void updateWidgetsSize();

    InfoBar *getInfoBar();

    BotField *getFieldBot() const;
    PlayerField *getFieldPlayer() const;

    Bot *getBot();

    void resetGame();
    void finishGame(Winner win);

    bool gameStart;

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:


    Ui::Widget *ui;

    PlayerField *fieldPlayer;
    BotField *fieldBot;

    ToolsBar *toolsBar;

    InfoBar *infoBar;

    Bot *bot;
};
#endif // WIDGET_H
