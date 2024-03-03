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
    groupBoxPosWhenPress = QPoint(x(), y());
    qDebug() << "Вызвался конструктор";
}

uint Ship::getMk()
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
    groupBoxPosWhenPress = QPoint(x(), y());
    repaint();
}

void Ship::rotate()
{
    QSize oldSize = size();
    Orientation oldOr = orientation;
    if(orientation == Orientation::vertical) {
        setGeometry(x(), y(), field->getSquareSize(), field->getSquareSize() * mk);
        orientation = Orientation::horizontal;
    }
    else {
        setGeometry(x(), y(),field->getSquareSize() * mk, field->getSquareSize());
        orientation = Orientation::vertical;
    }
    for(auto const &ship : allShips){
        if(checkCollision(QPoint(x(), y()), ship)) {
           // setGeometry(x(), y(), oldSize.width(), oldSize.height());
           // orientation = oldOr;
            //return;
        }
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
        groupBoxPosWhenPress = QPoint(x(), y());
    }
    else if(e->button() == Qt::MouseButton::RightButton){
        rotate();
    }
}

void Ship::mouseReleaseEvent(QMouseEvent *e)
{
    isTarget = false;
    bool isOnOtherShip = false;
    QPoint nearSquare = QPoint((x() + field->getSquareSize() / 2) / field->getSquareSize(), (y() + field->getSquareSize() / 2) / field->getSquareSize());
    QPoint newPos = nearSquare * field->getSquareSize();

    for(auto const &ship : allShips){
        if(ship != this){
            if(checkCollision(newPos, ship)){
                move(groupBoxPosWhenPress);
                isOnOtherShip = true;
                break;
            }
        }
        else isOnOtherShip = false;
    }
    if (!isOnOtherShip) move(newPos);
}

void Ship::mouseMoveEvent(QMouseEvent *e)
{
    if(isTarget){
        move(e->position().x() + x() - mousePosWhenPress.x(), e->position().y() + y() - mousePosWhenPress.y());
    }
}

bool Ship::checkCollision(QPoint const &newPos, auto const &ship)
{
    if(newPos == ship->pos()) return true;
    else if(newPos.x() == ship->x() && ship->y() > newPos.y() && ship->y() < newPos.y() + height()) // равны по x
        return true;
    else if(newPos.x() == ship->x() && newPos.y() > ship->y() && newPos.y() < ship->y() + ship->height())
        return true;
    else if(newPos.y() == ship->y() && newPos.x() > ship->x() && newPos.x() < ship->x() + ship->width()) // равны по y
        return true;
    else if(newPos.y() == ship->y() && ship->x() > newPos.x() && ship->x() < newPos.x() + width())
        return true;
    else if(newPos.x() > ship->x() && newPos.x() < ship->x() + ship->width() && ship->y() > newPos.y() && ship->y() < newPos.y() + height())// x и y не равны
        return true;
    else if(newPos.y() > ship->y() && newPos.y() < ship->y() + ship->height() && ship->x() > newPos.x() && ship->x() < newPos.x() + width())// x и y не равны
        return true;
    else return false;
}

ShipMk4::ShipMk4(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 4;
    allShips.push_back(this);
}

ShipMk3::ShipMk3(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 3; 
    allShips.push_back(this);
}

ShipMk2::ShipMk2(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 2;
    allShips.push_back(this);
}

ShipMk1::ShipMk1(QWidget *parent, Field *field)
    : Ship(parent, field)
{
    mk = 1;
    allShips.push_back(this);
}


