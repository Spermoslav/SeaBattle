#ifndef SHIPS_H
#define SHIPS_H

#include "field.h"

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>

class ShipMk4;
class ShipMk3;
class ShipMk2;
class ShipMk1;

class Ships : public QGroupBox
{
public:
    Ships(QWidget *parent);

private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    QWidget *parent;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk4 : public Ships
{
public:
    ShipMk4(QWidget *parent);

private slots:

private:

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk3 : public Ships
{
public:
    ShipMk3(QWidget *parent);

private slots:

private:

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk2 : public Ships
{
public:
    ShipMk2(QWidget *parent);

private slots:

private:

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ShipMk1 : public Ships
{
public:
    ShipMk1(QWidget *parent);

private slots:

private:

};

#endif // SHIPS_H
