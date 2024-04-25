#ifndef NEWCHECK_H
#define NEWCHECK_H

#include <QWidget>
#include <QPrintPreviewWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class newCheck; }
QT_END_NAMESPACE

class newCheck : public QWidget
{
    Q_OBJECT

public:
    newCheck(QWidget *parent = nullptr);
    ~newCheck();

    Ui::newCheck* getUi();

private:
    Ui::newCheck *ui;

    QPrintPreviewWidget printPreviewWidget;

public slots:
    void slotOnClearButton();
    void slotOnDeleteButton();
    void slotOnReButton();
    void slotOnBeginButton();
    void slotOnSignButton();
    void updateScreenshots();
    void slotOnSaveButton();
    void slotOnDeleteAllButton();
    void slotOnPreviewButton();
    void slotOnExportButton();
};
#endif // NEWCHECK_H
