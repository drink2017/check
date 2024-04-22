#include "newcheck.h"
#include "ui_newcheck.h"
#include "commandmanager.h"
#include "screenshotview.h"

#include <QDateTime>
#include <QDebug>

newCheck::newCheck(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newCheck)
{
    ui->setupUi(this);
    setWindowTitle("校核");
    setFixedSize(633,652);

    connect(ui->pushButton_clear,&QPushButton::clicked,this,&newCheck::slotOnClearButton);
    connect(ui->pushButton_delete,&QPushButton::clicked,this,&newCheck::slotOnDeleteButton);
    connect(ui->pushButton_re,&QPushButton::clicked,this,&newCheck::slotOnReButton);
    connect(ui->pushButton_begin,&QPushButton::clicked,this,&newCheck::slotOnBeginButton);
    connect(ui->pushButton_sign,&QPushButton::clicked,this,&newCheck::slotOnSignButton);
    connect(ui->verticalScrollBar,&QScrollBar::valueChanged,this,&newCheck::changeScreenshot);

    //签名icon
    QPixmap sign;
    if(sign.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg")){
        ui->label_sign->setPixmap(sign);
        ui->label_sign->setScaledContents(true);
    }

    //截图显示
    ui->label_screenshot->setText("未有截图");

    //拉动条
    QString styleSheet = "QScrollBar { background-color: gray; }";
    ui->verticalScrollBar->setStyleSheet(styleSheet);
    ui->verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    ui->verticalScrollBar->setPageStep(1);
}

newCheck::~newCheck()
{
    delete ui;
}

void newCheck::slotOnClearButton(){
    commandManager::getInstance()->screenshots.clear();
    updateScreenshots();
}

void newCheck::slotOnDeleteButton(){
    if(!commandManager::getInstance()->screenshots.isEmpty()){
        commandManager::getInstance()->screenshotValue = ui->verticalScrollBar->value();
        commandManager::getInstance()->screenshots.takeAt(commandManager::getInstance()->screenshotValue);
        if(commandManager::getInstance()->screenshotValue >= 1){
            commandManager::getInstance()->screenshotValue -= 1;
        }
        updateScreenshots();
    }
}

void newCheck::slotOnReButton(){
    screenshotView* w = screenshotView::getInstance();
    commandManager::getInstance()->screenshotValue = ui->verticalScrollBar->value();
    w->setType(shotType::replace);
    w->setCheck(this);
    w->show();
}

void newCheck::slotOnBeginButton(){
    screenshotView* w = screenshotView::getInstance();
    commandManager::getInstance()->screenshotValue = ui->verticalScrollBar->value();
    w->setType(shotType::newShot);
    w->setCheck(this);
    w->show();
}

void newCheck::slotOnSignButton(){
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_current->setText(currentTime);
    ui->pushButton_sign->setEnabled(false);
}

void newCheck::updateScreenshots(){
    ui->verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    QPixmap screenshot;
    if(commandManager::getInstance()->screenshots.size() == 0){
        ui->label_screenshot->setText("未有照片");
    }else{
        screenshot = commandManager::getInstance()->screenshots.at(commandManager::getInstance()->screenshotValue).scaled(ui->label_screenshot->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->label_screenshot->setPixmap(screenshot);
    }
}

void newCheck::changeScreenshot(int value){
    if(commandManager::getInstance()->screenshots.size() > 0){
        QPixmap screenshot;
        screenshot = commandManager::getInstance()->screenshots.at(value).scaled(ui->label_screenshot->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->label_screenshot->setPixmap(screenshot);
    }
}

void newCheck::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15;

    // 根据滚轮滚动方向更新当前显示的图片索引
    int currentImageIndex = ui->verticalScrollBar->value();
    currentImageIndex -= numSteps;

    // 处理边界情况，确保图片索引在合法范围内
    if (currentImageIndex < 0)
        currentImageIndex = 0;
    else if (currentImageIndex >= commandManager::getInstance()->screenshots.size())
        currentImageIndex = commandManager::getInstance()->screenshots.size() - 1;

    ui->verticalScrollBar->setValue(currentImageIndex);

    // 在label中显示对应索引的图片
    changeScreenshot(currentImageIndex);

    event->accept();
}









