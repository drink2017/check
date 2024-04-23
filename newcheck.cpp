#include "newcheck.h"
#include "ui_newcheck.h"
#include "commandmanager.h"
#include "screenshotview.h"
#include "screenshotlabel.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QThread>

newCheck::newCheck(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newCheck)
{
    ui->setupUi(this);
    setWindowTitle("校核");
    setFixedSize(633,652);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    ui->label_screenshot->check = this;

    connect(ui->pushButton_clear,&QPushButton::clicked,this,&newCheck::slotOnClearButton);
    connect(ui->pushButton_delete,&QPushButton::clicked,this,&newCheck::slotOnDeleteButton);
    connect(ui->pushButton_re,&QPushButton::clicked,this,&newCheck::slotOnReButton);
    connect(ui->pushButton_begin,&QPushButton::clicked,this,&newCheck::slotOnBeginButton);
    connect(ui->pushButton_sign,&QPushButton::clicked,this,&newCheck::slotOnSignButton);
    connect(ui->verticalScrollBar,&QScrollBar::valueChanged,ui->label_screenshot,&screenshotLabel::changeScreenshot);
    connect(ui->pushButton_deleteAll,&QPushButton::clicked,this,&newCheck::slotOnDeleteAllButton);

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
            ui->verticalScrollBar->setValue(commandManager::getInstance()->screenshotValue);
        }
        updateScreenshots();
    }
}

void newCheck::slotOnReButton(){
    if(!commandManager::getInstance()->screenshots.isEmpty()){
        showMinimized();
        QThread::msleep(250);
        screenshotView* w = screenshotView::getInstance();
        commandManager::getInstance()->screenshotValue = ui->verticalScrollBar->value();
        w->setType(shotType::replace);
        w->setCheck(this);
        w->setWindowState(Qt::WindowActive);
        w->show();
    }
}

void newCheck::slotOnBeginButton(){
    showMinimized();
    QThread::msleep(250);
    screenshotView* w = screenshotView::getInstance();
    commandManager::getInstance()->screenshotValue = ui->verticalScrollBar->value();
    w->setType(shotType::newShot);
    w->setCheck(this);
    w->setWindowState(Qt::WindowActive);
    w->show();
}

void newCheck::slotOnSignButton(){
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_current->setText(currentTime);
    ui->pushButton_sign->setEnabled(false);
    ui->pushButton_re->setEnabled(false);
    ui->pushButton_begin->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);
    ui->lineEdit_topic->setEnabled(false);
    ui->textEdit->setEnabled(false);
}

void newCheck::updateScreenshots(){
    ui->verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    QPixmap screenshot;
    if(commandManager::getInstance()->screenshots.size() == 0){
        ui->label_screenshot->setText("未有截图");
    }else{
        screenshot = commandManager::getInstance()->screenshots.at(commandManager::getInstance()->screenshotValue).scaled(ui->label_screenshot->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->label_screenshot->setPixmap(screenshot);
    }
}

void newCheck::slotOnDeleteAllButton(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"confirmation","Are you sure you want to delete?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QWidget::close();
    }
}

Ui::newCheck* newCheck::getUi(){
    return ui;
}









