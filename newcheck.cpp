#include "newcheck.h"
#include "ui_newcheck.h"
#include "screenshotview.h"

newCheck::newCheck(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newCheck)
{
    ui->setupUi(this);
    setWindowTitle("校核");
    setFixedSize(633,652);

    connect(ui->pushButton_begin,&QPushButton::clicked,this,&newCheck::slotOnBeginButton);

    QPixmap sign;
    if(sign.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg")){
        ui->label_sign->setPixmap(sign);
        ui->label_sign->setScaledContents(true);
    }

    QPixmap screenshot;
    if(screenshot.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg")){
        screenshot = screenshot.scaled(ui->label_screenshot->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->label_screenshot->setPixmap(screenshot);
    }

    QString styleSheet = "QScrollBar:vertical {"
                         "    background-color: #F0F0F0;"
                         "    width: 20px;"
                         "}"
                         "QScrollBar::handle:vertical {"
                         "    background-color: #909090;"
                         "    min-height: 30px;"
                         "}"
                         "QScrollBar::add-line:vertical {"
                         "    background-color: #E0E0E0;"
                         "    height: 20px;"
                         "    subcontrol-position: bottom;"
                         "    subcontrol-origin: margin;"
                         "}"
                         "QScrollBar::sub-line:vertical {"
                         "    background-color: #E0E0E0;"
                         "    height: 20px;"
                         "    subcontrol-position: top;"
                         "    subcontrol-origin: margin;"
                         "}";
    ui->verticalScrollBar->setStyleSheet(styleSheet);
}

newCheck::~newCheck()
{
    delete ui;
}

void newCheck::slotOnBeginButton(){
    screenshotView* w = screenshotView::getInstance();
    w->show();
}

