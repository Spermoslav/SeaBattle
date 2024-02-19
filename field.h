#ifndef FIELD_H
#define FIELD_H



#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QPainter>

class Ships;
class ShipMk4;
class ShipMk3;
class ShipMk2;
class ShipMk1;


class Field : public QGroupBox
{
    Q_OBJECT
public:
    Field(QWidget *parent);

    int getSquareSize();
    int const getSquareCount();

    void updateSquareSize();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    QWidget *parent;

    ShipMk3 *mk1;

    int squareSize;
    int const squareCount = 10;
};

#endif // FIELD_H
