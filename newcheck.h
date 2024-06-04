#ifndef NEWCHECK_H
#define NEWCHECK_H

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>

#include "screenshotlabel.h"
#include "UiMainWindow.h"

class newCheck : public UiMainWindow
{
public:
    newCheck();
    ~newCheck();

    void updateListWidget();

private:
    QVBoxLayout *verticalLayout;               //整体布局
    QLabel *label;                             //项目名称和编码
    QHBoxLayout *horizontalLayout;             //校核主题布局
    QLabel *label_3;                           //校核主题
    QLineEdit *lineEdit;                       //校核主题输入
    QHBoxLayout *horizontalLayout_5;           //校核人和校核时间布局
    QLabel *label_4;                           //校核人
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;                           //校核时间
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;                   //截图
    QPushButton *pushButton_2;                 //重截
    QPushButton *pushButton_3;                 //删除
    QPushButton *pushButton_4;                 //清空
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;                           //显示当前页数
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *listWidget;                   //显示缩略图
    screenshotLabel *label_5;                  //显示图片
    QTextEdit *textEdit;                       //输入校核说明
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_5;                 //预览
    QPushButton *pushButton_6;                 //签字
    QPushButton *pushButton_7;                 //导出
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_9;                 //取消
    QPushButton *pushButton_8;                 //确定

    QScrollBar *verticalScrollBar;

    void setupWidgets(UiMainWindow* Widget);
    void retranslateUi();

    void write();
    void read();

    bool messageBoxIsShowing = false;

    bool generatePDF(QString filePath);
    int page = 1;

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
    void slotOnPreviewButton();
    void slotOnListItemSelection();
    void slotOnTextChanged();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // NEWCHECK_H
