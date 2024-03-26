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
    isDestroy = false;
    destroyItems = 0;
    orientation = Orientation::vertical;

    if(field->getAllShips().size() >= 6) mk = 1;
    else if(field->getAllShips().size() >= 3) mk = 2;
    else if(field->getAllShips().size() >= 1) mk = 3;
    else if(field->getAllShips().size() == 0) mk = 4;

    for(size_t i = 0; i < mk; i++) {
        damage.push_back(new Damage(this));
        damage[i]->move(0, i * field->getSquareSize());
    }
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
    QPoint newPos = field->findNearSquarePos(pos());
    if(orientation == Orientation::vertical) {
        setGeometry(newPos.x(), newPos.y(), field->getSquareSize(), field->getSquareSize() * mk);
        shipSize = QSize(field->getSquareSize() / 1.5, field->getSquareSize() / 1.5 * mk);
        for(size_t i = 0; i < damage.size(); i++) {
            damage[i]->move(0, i * field->getSquareSize());
            damage[i]->resize();
        }
    }
    else {
        setGeometry(newPos.x(), newPos.y(), field->getSquareSize() * mk, field->getSquareSize());
        shipSize = QSize(field->getSquareSize() / 1.5 * mk, field->getSquareSize() / 1.5);
        for(size_t i = 0; i < damage.size(); i++) {
            damage[i]->move(i * field->getSquareSize(), 0);
            damage[i]->resize();
        }
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
    if(orientation == vertical) {
        orientation = horizontal;
        setGeometry(x(), y(),field->getSquareSize() * mk, field->getSquareSize());
    }
    else {
        orientation = vertical;
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
    int count = 0;
    while(count < 1000) {
        ++count;
        if (count == 999) qDebug() << pos() << size() << mk;
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

void Ship::takeDamage(const QPoint &damagePos)
{
    for(auto const &dm : damage) {
        if(findPosForDamage(damagePos) == dm->pos()){
            dm->show();
            if(++destroyItems == mk) {
                isDestroy = true;
                update();
            }
        }
        else {
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
    if(isDestroy || field->getIsPlayerField()) {
        QPainter p;
        p.begin(this);
        p.drawRect(0, 0, width() - 1, height() - 1);
        p.setBrush(Qt::blue);
        p.drawRect(shipPos.x(), shipPos.y(), shipSize.width(), shipSize.height());
        p.end();
    }
}

void Ship::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::MouseButton::LeftButton) {
        if(!field->getIsPlayerField()) {
            takeDamage(e->pos());
            return;
        }
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
    QPoint newPos = field->findNearSquarePos(pos());

    for(auto const &ship : field->getAllShips()){
        if(ship != this){
            if(checkCollision(newPos, ship)){
                move(groupBoxPosWhenPress);
                return;
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
    else return false;
}

bool Ship::checkFieldCollision(const QPoint &newPos)
{
    if(newPos.x() + width() > field->width() || newPos.x() < 0) return true;
    else if(newPos.y() + height() > field->height() || newPos.y() < 0) return true;
    else return false;
}

QPoint Ship::findPosForDamage(const QPoint &pos)
{
    return QPoint((pos.x() / field->getSquareSize()),
                  (pos.y() / field->getSquareSize())) * field->getSquareSize();
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Damage::Damage(Ship *parent)
    : QWidget(parent)
{
    this->parent = parent;
    hide();
    update();
}

void Damage::resize()
{
    static_cast<QWidget*> (this)->resize(parent->getField().getSquareSize(), parent->getField().getSquareSize());
}

void Damage::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p;
    p.begin(this);
    p.setPen(Qt::blue);
    p.drawLine(QPoint(0, 0), QPoint(width(), height()));
    p.drawLine(QPoint(width(), 0), QPoint(0, height()));
    p.end();
}

void Damage::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    update();
}
