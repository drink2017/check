#ifndef CHECK_H
#define CHECK_H

#include <QLabel>
#include <QScrollBar>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLineEdit>

#include "UiMainWindow.h"
#include "screenshotlabel.h"

class check : public UiMainWindow
{
public:
    check(QWidget *parent = nullptr);
    ~check();

private:
    QVBoxLayout *verticalLayout;
    QLabel *label_info;
    QHBoxLayout *horizontalLayout;
    QLabel *label_topic;
    QLineEdit *lineEdit_topic;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_begin;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_re;
    QPushButton *pushButton_clear;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QLabel *label_sign;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_check;
    QLabel *label_time;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_sign;
    QPushButton *pushButton_export;
    QPushButton *pushButton_deleteAll;
    QPushButton *pushButton_save;
    QScrollBar *verticalScrollBar;
    screenshotLabel *label_screenshot;
    QLabel *label_headline;

    void setupWidgets(UiMainWindow* newCheck);
    void retranslateUi();

    void generatePDF(QString filePath);

    bool messageBoxIsShowing = false;

public slots:
    void slotOnClearButton();
    void slotOnDeleteButton();
    void slotOnReButton();
    void slotOnBeginButton();
    void slotOnSignButton();
    void updateScreenshots();
    //void slotOnSaveButton();
    void slotOnDeleteAllButton();
    void slotOnExportButton();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CHECK_H
