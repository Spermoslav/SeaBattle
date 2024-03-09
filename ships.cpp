#include "ships.h"
#include "field.h"

class Field;

Ship::Ship(Field *field)
    : QGroupBox(field)
{
    this->field = field;
    isTarget = false;
    shipCenterX = width() / 2;
    shipCenterY = height() / 2;
    orientation = Orientation::vertical;

    shipSize = QSize(field->getSquareSize() / 1.5, field->getSquareSize() / 1.5 * mk);
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

    if(field->getIsPlayerField()){
        for(auto const &ship : playerShips){
            if(ship != this) {
                if(checkCollision(QPoint(x(), y()), ship)) {
                    setGeometry(x(), y(), oldSize.width(), oldSize.height());
                    orientation = oldOr;
                    return;
                }
            }
        }
    }
    else {
        for(auto const &ship : botShips){
            if(ship != this) {
                if(checkCollision(QPoint(x(), y()), ship)) {
                    setGeometry(x(), y(), oldSize.width(), oldSize.height());
                    orientation = oldOr;
                    return;
                }
            }
        }
    }
    resize();
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

    if(field->getIsPlayerField()){
        for(auto const &ship : playerShips){
            if(ship != this){
                if(checkCollision(newPos, ship)){
                    move(groupBoxPosWhenPress);
                    return;
                }
            }
        }
    }
    else {
        for(auto const &ship : botShips){
            if(ship != this){
                if(checkCollision(newPos, ship)){
                    move(groupBoxPosWhenPress);
                    return;
                }
            }
        }
    }
    move(newPos);
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

    int sqSize = field->getSquareSize();
    if(newPos == ship->pos()) return true;
    else if(newPos.x() + width() > field->width() || newPos.x() < 0) return true; // за пределами поля
    else if(newPos.y() + height() > field->height() || newPos.y() < 0) return true;
    else if(newPos.x() >= ship->x() - sqSize && newPos.x() < ship->x() + ship->width() + sqSize && // проверка вхождения x и y target корабля в другой корабль
            newPos.y() >= ship->y() - sqSize && newPos.y() < ship->y() + ship->height() + sqSize) {
        qDebug() << "xuy";
            return true;
    }
    else if(newPos.x() + width() > ship->x() - sqSize && newPos.x() + width() <= ship->x() + ship->width() + sqSize && // проверка вхождения x + width() и
            newPos.y() + height() > ship->y() - sqSize && newPos.y() + height() <= ship->y() + ship->height() + sqSize) { // y + height() target корабля в другой корабль
            return true;
    }
//    else if(ship->x() >= newPos.x() - sqSize && ship->x() < newPos.x() + width() + sqSize && // проверка вхождения x и y другого корабля в target корабль
//            ship->y() >= newPos.y() - sqSize && ship->y() < newPos.y() + height() + sqSize) {
//        qDebug() << "2";
//        return true;
//    }
}

ShipMk4::ShipMk4(Field *field)
    : Ship(field)
{
    mk = 4;
    if(field->getIsPlayerField()) playerShips.push_back(this);
    else botShips.push_back(this);
}

ShipMk3::ShipMk3(Field *field)
    : Ship(field)
{
    mk = 3; 
    if(field->getIsPlayerField()) playerShips.push_back(this);
    else botShips.push_back(this);
}

ShipMk2::ShipMk2(Field *field)
    : Ship(field)
{
    mk = 2;
    if(field->getIsPlayerField()) playerShips.push_back(this);
    else botShips.push_back(this);
}

ShipMk1::ShipMk1(Field *field)
    : Ship(field)
{
    mk = 1;
    if(field->getIsPlayerField()) playerShips.push_back(this);
    else botShips.push_back(this);
}


