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

    QList<QPixmap> screenshots;

public slots:
    void slotOnBeginButton();
};
#endif // NEWCHECK_H
