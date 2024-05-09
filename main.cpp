#include "game/game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game w;
    w.setMinimumSize(400, 400);
    w.show();
    return a.exec();
}
