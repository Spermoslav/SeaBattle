#include "ships.h"
#include "field.h"
#include "tools.h"

const QColor Ship::PLAYER_COLOR = QColor(0, 150, 255);
const QColor Ship::BOT_COLOR    = QColor(255, 70, 70);

Ship::Ship(Field *field)
    : QGroupBox(field)
{
    this->field = field;
    infoBar = field->getParent()->infoBar;
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
    qDebug() << field->getSquareSize() << size() << mk;
    repaint();
}

void Ship::rotate()
{
    QSize oldSize = size();
    Orientation oldOr = orientation;

    turn();

    for(auto const &ship : field->getAllShips()){
        if(ship != this) {
            if(checkCollision(QPoint(x(), y()), ship)) {
                setGeometry(x(), y(), oldSize.width(), oldSize.height());
                orientation = oldOr;
                resize();
                return;
            }
        }
    }
}

void Ship::randomMove()
{
    QList<QPoint> correctPlaces;
    quint8 index;
    bool allShipsSuit = false;
    if(rand() % 2) turn();

    for(int i = 0; i < Field::ROWS_COUNT; ++i) {
        for(int j = 0; j < Field::ROWS_COUNT; ++j) {
            correctPlaces.push_back(QPoint(i * field->getSquareSize(), j * field->getSquareSize()));
        }
    }

    for(size_t count = 0; count < Field::SQUARES_COUNT; ++count) {
        index = rand() % correctPlaces.size();
        for (const auto &s : field->getAllShips()) {
            if(s != this) {
                if(checkCollision(correctPlaces[index], s)) {
                    correctPlaces.removeAt(index);
                    allShipsSuit = false;
                    break;
                }
                else {
                    allShipsSuit = true;
                }
            }
        }
        if(allShipsSuit) {
            move(correctPlaces[index]);
            return;
        }
    }
}

void Ship::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)

}

bool Ship::checkCollision(const QPoint &newPos, const Ship *ship) const
{
    return checkShipCollision(newPos, ship) || checkFieldCollision(newPos);
}

bool Ship::checkShipCollision(const QPoint &newPos, const Ship *ship) const
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

bool Ship::checkFieldCollision(const QPoint &newPos) const
{
    if(newPos.x() + width() > field->width() || newPos.x() < 0) return true;
    else if(newPos.y() + height() > field->height() || newPos.y() < 0) return true;
    else return false;
}

void Ship::reset()
{
    for(auto const &dm : damage) {
        dm->hide();
    }
    isTarget     = false;
    isDestroy    = false;
    destroyItems = 0;
    orientation  = vertical;
    move(0, 0);
    resize();
    update();
}

QPoint Ship::findPosForDamage(const QPoint &pos) const
{
    return QPoint((pos.x() / field->getSquareSize()),
                  (pos.y() / field->getSquareSize())) * field->getSquareSize();
}

void Ship::turn()
{
    if(orientation == vertical) {
        orientation = horizontal;
        setGeometry(x(), y(),field->getSquareSize() * mk, field->getSquareSize());
    }
    else {
        orientation = vertical;
        setGeometry(x(), y(), field->getSquareSize(), field->getSquareSize() * mk);
    }
    resize();
}

bool PlayerShip::takeDamage(const QPoint &damagePos)
{
    for(auto const &dm : damage) {
        if(findPosForDamage(damagePos) == dm->pos() && dm->isHidden()){
            dm->show();
            infoBar->botScoreAdd();
            if(++destroyItems == mk) {
                isDestroy = true;
                infoBar->botDestroyShipsAdd();
                field->shipDestroyed(this);
                update();
            }
            return isDestroy;
        }
    }
    return false;
}

void PlayerShip::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p;
    p.begin(this);
    if(isDestroy) {
        p.setBrush(Field::MISSHIT_COLOR);
        p.drawRect(0, 0, width(), height());
    }
    p.setBrush(Ship::PLAYER_COLOR);
    p.drawRect(shipPos.x(), shipPos.y(), shipSize.width(), shipSize.height());
    p.end();
}

void PlayerShip::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::MouseButton::LeftButton) {
        if(field->getParent()->getGameStatus() == finished) {
            isTarget = true;
            mousePosWhenPress = e->position().toPoint();
            groupBoxPosWhenPress = QPoint(x(), y());
        }
    }
    else if(e->button() == Qt::MouseButton::RightButton && field->getParent()->getGameStatus() == finished){
        rotate();
    }
}

void PlayerShip::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(isTarget) {
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
}

void PlayerShip::mouseMoveEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(isTarget){
        move(e->position().x() + x() - mousePosWhenPress.x(), e->position().y() + y() - mousePosWhenPress.y());
    }
}


bool BotShip::takeDamage(const QPoint &damagePos)
{
    for(auto const &dm : damage) {
        if(findPosForDamage(damagePos) == dm->pos() && dm->isHidden()){
            dm->show();
            infoBar->playerScoreAdd();
            if(++destroyItems == mk) {
                isDestroy = true;
                infoBar->playerDestroyShipsAdd();
                field->shipDestroyed(this);
                update();
            }
            return isDestroy;
        }
    }
    return false;
}

void BotShip::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

#ifdef BOT_SHIPS_SHOW
    QPainter p;
    p.begin(this);
    if(isDestroy) {
        p.setBrush(Field::MISSHIT_COLOR);
        p.drawRect(0, 0, width(), height());
    }
    p.setBrush(Ship::BOT_COLOR);
    p.drawRect(shipPos.x(), shipPos.y(), shipSize.width(), shipSize.height());
    p.end();
#else
    if(isDestroy || field->getParent()->getGameStatus() == over) {
        QPainter p;
        p.begin(this);
        if(isDestroy) {
            p.setBrush(Field::MISSHIT_COLOR);
            p.drawRect(0, 0, width(), height());
        }
        p.setBrush(Qt::red);
        p.drawRect(shipPos.x(), shipPos.y(), shipSize.width(), shipSize.height());
        p.end();
    }
#endif // DEBUG
}

void BotShip::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
#ifndef GAME_QUEUEMOVE_LOCK
    if(field->getParent()->getGameStatus() == started && field->getParent()->getWhoMove() == Gamer::player) {
        takeDamage(e->pos());
    }
#else
    if(field->getParent()->getGameStatus() == started) {
        takeDamage(e->pos());
    }
#endif
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
    static_cast<QWidget*> (this)->resize(parent->getField()->getSquareSize(), parent->getField()->getSquareSize());
}

void Damage::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p;
    QPen pen;
    pen.setWidthF(1.5);
    p.begin(this);
    p.setPen(pen);
    p.drawLine(QPoint(0, 0), QPoint(width(), height()));
    p.drawLine(QPoint(width(), 0), QPoint(0, height()));
    p.end();
}

void Damage::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    update();
}
