#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>

#include "field.h"
#include "tools.h"
#include "ships.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void updateWidgetsSize();

    InfoBar &getInfoBar() const;

    Field &getFieldBot() const;
    Field &getFieldPlayer() const;

    bool gameStart;

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:

    Ui::Widget *ui;

    Field *fieldPlayer;
    Field *fieldBot;

    ToolsBar *toolsBar;

    InfoBar *infoBar;


};
#endif // WIDGET_H
