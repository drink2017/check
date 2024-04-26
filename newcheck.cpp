#include "newcheck.h"
#include "ui_newcheck.h"
#include "commandmanager.h"
#include "screenshotview.h"
#include "screenshotlabel.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QThread>

#include <QPdfWriter>
#include <QtPrintSupport/QPrinter>
#include <QBuffer>
#include <QDesktopServices>
#include <QFileDialog>
#include <QTextDocument>

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
    connect(ui->pushButton_save,&QPushButton::clicked,this,&newCheck::slotOnSaveButton);
    connect(ui->pushButton_deleteAll,&QPushButton::clicked,this,&newCheck::slotOnDeleteAllButton);
    connect(ui->pushButton_preview,&QPushButton::clicked,this,&newCheck::slotOnPreviewButton);
    connect(ui->pushButton_export,&QPushButton::clicked,this,&newCheck::slotOnExportButton);

//    //签名icon
//    QPixmap sign;
//    if(sign.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg")){
//        ui->label_sign->setPixmap(sign);
//        ui->label_sign->setScaledContents(true);
//    }

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
    QPixmap sign;
    if(sign.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg")){
        ui->label_sign->setPixmap(sign);
        ui->label_sign->setScaledContents(true);
    }

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

struct info{
    QString basicInfo;
    QString topic;
    QString checkMan;
    QString checkTime;
    QList<QPixmap> screenshots;
    QString illustrate;
};

void newCheck::slotOnSaveButton(){
    info myInfo;
    myInfo.basicInfo = ui->label_basic->text();
    myInfo.topic = ui->label_topic->text();
    myInfo.checkMan = ui->label_name->text();
    myInfo.checkTime = ui->label_time->text();
    myInfo.screenshots = commandManager::getInstance()->screenshots;
    myInfo.illustrate = ui->textEdit->toPlainText();
}

void newCheck::slotOnPreviewButton(){
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);

    QString filePath = "output.pdf";
    QPdfWriter pdfWriter(&buffer);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    int currentPage = 0;

    for(const QPixmap& pixmap : commandManager::getInstance()->screenshots){
        if(currentPage != 0){
            pdfWriter.newPage();
            currentPage += 1;
        }else{
            currentPage += 1;
        }
        painter.drawPixmap(pixmap.rect(), pixmap,pixmap.rect());
    }

    buffer.close();

    //QPrinter printer;

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void newCheck::slotOnExportButton(){
    QString filePath = QFileDialog::getSaveFileName(this, QStringLiteral("导出QGradient预设值"), QString(), "*.pdf");
    if (filePath.isEmpty()) {
        return;
    }
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    for(const QPixmap& pixmap : commandManager::getInstance()->screenshots){
        painter.drawPixmap(painter.viewport(), pixmap,pixmap.rect());
        //pdfWriter.newPage();
    }
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









