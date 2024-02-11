#ifndef FIELD_H
#define FIELD_H

#include "ships.h"

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>

class Field : public QGroupBox
{
    Q_OBJECT
public:
    Field(QWidget *parent);

private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    QWidget *parent;
};

#endif // FIELD_H
