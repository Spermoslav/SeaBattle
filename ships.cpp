#include "ships.h"
#include "field.h"
#include <thread>
#include <chrono>

class Field;

Ship::Ship(Field *field)
    : QGroupBox(field)
{
    this->field = field;
    isTarget = false;
    orientation = Orientation::vertical;

    if(field->getAllShips().size() >= 6) mk = 1;
    else if(field->getAllShips().size() >= 3) mk = 2;
    else if(field->getAllShips().size() >= 1) mk = 3;
    else if(field->getAllShips().size() == 0) mk = 4;

    resize();

    randomMove();
}

uint Ship::getMk()
{
    return mk;
}

Field &Ship::getField() const
{
    return *field;
}

bool Ship::getIsTarget()
{
    return isTarget;
}

void Ship::resize()
{
    QPoint nearSquare = QPoint((x() + field->getSquareSize() / 2) / field->getSquareSize(), (y() + field->getSquareSize() / 2) / field->getSquareSize());
    QPoint newPos = nearSquare * field->getSquareSize();
    if(orientation == Orientation::vertical) {
        setGeometry(newPos.x(), newPos.y(), field->getSquareSize(), field->getSquareSize() * mk);
        shipSize = QSize(field->getSquareSize() / 1.5, field->getSquareSize() / 1.5 * mk);
    }
    else {
        setGeometry(newPos.x(), newPos.y(), field->getSquareSize() * mk, field->getSquareSize());
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
        orientation = Orientation::horizontal;
        setGeometry(x(), y(),field->getSquareSize() * mk, field->getSquareSize());
    }
    else {
        orientation = Orientation::vertical;
        setGeometry(x(), y(), field->getSquareSize(), field->getSquareSize() * mk);
    }

    for(auto const &ship : field->getAllShips()){
        if(ship != this) {
            if(checkCollision(QPoint(x(), y()), ship)) {
                setGeometry(x(), y(), oldSize.width(), oldSize.height());
                orientation = oldOr;
                return;
            }
        }
    }
    resize();
}

void Ship::randomMove()
{
    QPoint newPos;
    int sqX, sqY;
    while(true) {
        bool allShipsCheck = false;
        sqX = rand() % (field->getSquareCount() + 1);
        sqY = rand() % (field->getSquareCount() + 1);
        newPos = QPoint(sqX * field->getSquareSize(), sqY * field->getSquareSize());
        if(rand() % 2) rotate();
        if(field->getAllShips().size() == 0) {
            if(checkFieldCollision(newPos)) {
                continue;
            }
            else {
                move(newPos);
                return;
            }
        }
        for(auto const &ship : field->getAllShips()){
            if(ship != this){
                if(checkCollision(newPos, ship)){
                    allShipsCheck = false;
                    break;
                }
                else allShipsCheck = true;
            }
        }
        if (allShipsCheck) {
            move(newPos);
            return;
        }
    }
}

void Ship::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
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
    if((e->position().x() >= shipPos.x() && e->position().x() <= shipSize.width() + shipPos.x() && e->button() == Qt::MouseButton::LeftButton)
            && (e->position().y() >= shipPos.y() && e->position().y() <= shipSize.height() + shipPos.y())) {
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
    Q_UNUSED(e)
    isTarget = false;
    QPoint nearSquare = QPoint((x() + field->getSquareSize() / 2) / field->getSquareSize(), (y() + field->getSquareSize() / 2) / field->getSquareSize());
    QPoint newPos = nearSquare * field->getSquareSize();

    for(auto const &ship : field->getAllShips()){
        if(ship != this){
            if(checkCollision(newPos, ship)){
                move(groupBoxPosWhenPress);
                return;
            }
        }
    }
    move(newPos);
    qDebug() << newPos;
}

void Ship::mouseMoveEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(isTarget){
        move(e->position().x() + x() - mousePosWhenPress.x(), e->position().y() + y() - mousePosWhenPress.y());
    }
}

bool Ship::checkCollision(QPoint const &newPos, auto const &ship)
{
    return checkShipCollision(newPos, ship) || checkFieldCollision(newPos);
}

bool Ship::checkShipCollision(const QPoint &newPos, auto const &ship)
{
    const int sqSize = field->getSquareSize();

    if(newPos == ship->pos()) return true;
    else if(newPos.x() >= ship->x() - sqSize && newPos.x() < ship->x() + ship->width() + sqSize && // проверка вхождения x и y target корабля в другой корабль
            newPos.y() >= ship->y() - sqSize && newPos.y() < ship->y() + ship->height() + sqSize) {
            return true;
    }
    else if(newPos.x() + width() > ship->x() - sqSize && newPos.x() + width() <= ship->x() + ship->width() + sqSize && // проверка вхождения x + width() и
            newPos.y() + height() > ship->y() - sqSize && newPos.y() + height() <= ship->y() + ship->height() + sqSize) { // y + height() target корабля в другой корабль
            return true;
    }
}

bool Ship::checkFieldCollision(const QPoint &newPos)
{
    int sqSize = field->getSquareSize();
    if(newPos.x() + width() > field->width() || newPos.x() < 0) return true;
    else if(newPos.y() + height() > field->height() || newPos.y() < 0) return true;
}

ShipMk4::ShipMk4(Field *field)
    : Ship(field)
{
    mk = 4;
}

ShipMk3::ShipMk3(Field *field)
    : Ship(field)
{
    mk = 3; 
}

ShipMk2::ShipMk2(Field *field)
    : Ship(field)
{
    mk = 2;
}

ShipMk1::ShipMk1(Field *field)
    : Ship(field)
{
    mk = 1;
}



