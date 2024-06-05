#include <QApplication>
#include <QDebug>

#include "newcheck.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    newCheck w;
    w.show();
    return a.exec();
}
