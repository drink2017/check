#ifndef NEWCHECK_H
#define NEWCHECK_H

#include <QWidget>
#include "UiMainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class newCheck; }
QT_END_NAMESPACE

class newCheck : public UiMainWindow
{
    Q_OBJECT

public:
    newCheck(QWidget *parent = nullptr);
    ~newCheck();

    Ui::newCheck* getUi();

private:
    Ui::newCheck *ui;

    void generatePDF(QString filePath);

public slots:
    void slotOnClearButton();
    void slotOnDeleteButton();
    void slotOnReButton();
    void slotOnBeginButton();
    void slotOnSignButton();
    void updateScreenshots();
    void slotOnSaveButton();
    void slotOnDeleteAllButton();
    void slotOnExportButton();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // NEWCHECK_H
