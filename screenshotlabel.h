#ifndef SCREENSHOTLABEL_H
#define SCREENSHOTLABEL_H

#include <QLabel>
#include <QScrollBar>
#include <QListWidget>

class screenshotLabel : public QLabel
{
public:
    screenshotLabel(QWidget* parent = nullptr);

    QScrollBar *verticalScrollBar;
    QLabel *label_headline;
    QListWidget* listWidget;

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    void changeScreenshot(int value);
};

#endif // SCREENSHOTLABEL_H
