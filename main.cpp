#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::srand(std::time(0));
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
