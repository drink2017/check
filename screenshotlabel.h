#ifndef SCREENSHOTLABEL_H
#define SCREENSHOTLABEL_H

#include "newcheck.h"

#include <QLabel>

class screenshotLabel : public QLabel
{
public:
    screenshotLabel(QWidget* parent = nullptr);

    newCheck* check;

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    void changeScreenshot(int value);
};

#endif // SCREENSHOTLABEL_H
