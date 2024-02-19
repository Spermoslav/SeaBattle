#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>

#include "field.h"
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

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    Ui::Widget *ui;

    Field *field;

    ShipMk2 *mk2;
    ShipMk3 *mk;
};
#endif // WIDGET_H
