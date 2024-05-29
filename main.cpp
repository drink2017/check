#include <QApplication>
#include <QDebug>

#include "newcheck.h"
//#include "check.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //check w;
    newCheck w;
    w.show();
    return a.exec();
}
