#ifndef NEWCHECK_H
#define NEWCHECK_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class newCheck; }
QT_END_NAMESPACE

class newCheck : public QWidget
{
    Q_OBJECT

public:
    newCheck(QWidget *parent = nullptr);
    ~newCheck();

private:
    Ui::newCheck *ui;

public slots:
    void slotOnClearButton();
    void slotOnDeleteButton();
    void slotOnReButton();
    void slotOnBeginButton();
    void slotOnSignButton();
    void updateScreenshots();
    void changeScreenshot(int value);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
};
#endif // NEWCHECK_H
