#include "check.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    check w;
    w.show();
    return a.exec();
}
