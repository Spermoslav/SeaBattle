#include "ships.h"
#include "field.h"

class Field;

Ship::Ship(QWidget *parent, Field *field)
    : QGroupBox(parent)
{
    this->parent = parent;
    this->field = field;
    isTarget = false;
    shipCenterX = width() / 2;
    shipCenterY = height() / 2;
    orientation = Orientation::vertical;

    shipSize = QSize(field->getSquareSize() / 1.5, (field->getSquareSize() / 1.5) * mk);
    shipPos = QPoint((width() - shipSize.width()) / 2, (height() - shipSize.height()) / 2);
}

int Ship::getMk()
{
    return mk;
}

bool Ship::getIsTarget()
{
    return isTarget;
}

void Ship::resize()
{
    if(orientation == Orientation::vertical) {
        setGeometry(x(), y(), field->getSquareSize(), field->getSquareSize() * mk);
        shipSize = QSize(field->getSquareSize() / 1.5, field->getSquareSize() / 1.5 * mk);
    }
    else {
        setGeometry(x(), y(), field->getSquareSize() * mk, field->getSquareSize());
        shipSize = QSize(field->getSquareSize() / 1.5 * mk, field->getSquareSize() / 1.5);
    }
    shipPos = QPoint((width() - shipSize.width()) / 2, (height() - shipSize.height()) / 2);
    shipCenterX = width() / 2;
    shipCenterY = height() / 2;
    repaint();
}

void Ship::rotate()
{
    if(orientation == Orientation::vertical) {
        setGeometry(x(), y(), field->getSquareSize(), field->getSquareSize() * mk);
        orientation = Orientation::horizontal;
    }
    else {
        setGeometry(x(), y(), field->getSquareSize() * mk, field->getSquareSize());
        orientation = Orientation::vertical;
    }
}

void Ship::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    resize();
}

void Ship::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p;
    p.begin(this);
    p.drawRect(0, 0, width() - 1, height() - 1);
    p.setBrush(Qt::blue);
    p.drawRect(shipPos.x(), shipPos.y(), shipSize.width(), shipSize.height());

    p.end();
}

void Ship::mousePressEvent(QMouseEvent *e)
{
    if((e->x() >= shipPos.x() && e->x() <= shipSize.width() + shipPos.x() && e->button() == Qt::MouseButton::LeftButton)
            && (e->y() >= shipPos.y() && e->y() <= shipSize.height() + shipPos.y())) {
        isTarget = true;
        mousePosWhenPress = e->position().toPoint();
    }
    else if(e->button() == Qt::MouseButton::RightButton){
        rotate();
    }
    qDebug() << x() << y();
}

void Ship::mouseReleaseEvent(QMouseEvent *e)
{
    isTarget = false;
    QPoint nearSquare = QPoint((x() + field->getSquareSize() / 2) / field->getSquareSize(), (y() + field->getSquareSize() / 2) / field->getSquareSize());
    move(nearSquare * field->getSquareSize());
    qDebug() << x() << y() << nearSquare;
}

void Ship::mouseMoveEvent(QMouseEvent *e)
{
    if(isTarget){
        move(e->position().x() + x() - mousePosWhenPress.x(), e->position().y() + y() - mousePosWhenPress.y());
    }
}

ShipMk4::ShipMk4(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 4;

}

ShipMk3::ShipMk3(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 3;

}

ShipMk2::ShipMk2(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 2;
}

ShipMk1::ShipMk1(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 1;
}


