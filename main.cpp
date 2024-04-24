#include <QApplication>
#include "Minefield.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minefield w;
    w.show();
    return a.exec();
}
