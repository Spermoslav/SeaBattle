#include "game/widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setMinimumSize(400, 400);
    w.show();
    return a.exec();
}
