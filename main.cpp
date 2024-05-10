//#include "newcheck.h"
#include "check.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //newCheck w;
    //w.show();
    check w;
    w.show();
    return a.exec();
}
