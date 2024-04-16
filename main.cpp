//#include "newcheck.h"
#include "screenshotview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //newCheck w;
    //w.show();
    screenshotView* w = screenshotView::getInstance();
    w->show();
    return a.exec();
}
