#include "newcheck.h"
#include "ui_newcheck.h"
#include "commandmanager.h"
#include "screenshotview.h"
#include "screenshotlabel.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QtPrintSupport/QPrinter>
#include <QDesktopServices>
#include <QFileDialog>

newCheck::newCheck(QWidget *parent)
    : UiMainWindow(parent)
    , ui(new Ui::newCheck)
{
    //设置无边框
      //FramelessHelper* helper = this->framelessHelper();
      //设置样式
      this->setStyle(UiMainWindow::UiStyle::Light);
      //设置字体
      QFont font;
      font.setFamily("思源黑体");
      font.setPixelSize(13);
      this->setTitleFont(font);
      setMinimumSize(800, 600);       //设置最小尺寸（最小尺寸大小待定）
      setWindowState(Qt::WindowMaximized);//设定初始尺寸为“最大化”


    QIcon mainIcon(":/icons/newCheck/main.png");
    setWindowIcon(mainIcon);

    ui->setupUi(this);
    setWindowTitle("校核");
    //setFixedSize(631,773);
    //setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    //ui->label_screenshot->check = this;

    QIcon beginScreenshot(":/icons/newCheck/beginScreenshot.png");
    ui->pushButton_begin->setIcon(beginScreenshot);
    ui->pushButton_begin->setToolTip("开始截图");

    QIcon deleteScreenshot(":/icons/newCheck/delete.png");
    ui->pushButton_delete->setIcon(deleteScreenshot);
    ui->pushButton_delete->setToolTip("删除截图");

    QIcon replaceScreenshot(":/icons/newCheck/replace.png");
    ui->pushButton_re->setIcon(replaceScreenshot);
    ui->pushButton_re->setToolTip("重新截图");

    QIcon clearScreenshot(":/icons/newCheck/clear.png");
    ui->pushButton_clear->setIcon(clearScreenshot);
    ui->pushButton_clear->setToolTip("清空截图");

    connect(ui->pushButton_clear,&QPushButton::clicked,this,&newCheck::slotOnClearButton);
    connect(ui->pushButton_delete,&QPushButton::clicked,this,&newCheck::slotOnDeleteButton);
    connect(ui->pushButton_re,&QPushButton::clicked,this,&newCheck::slotOnReButton);
    connect(ui->pushButton_begin,&QPushButton::clicked,this,&newCheck::slotOnBeginButton);
    connect(ui->pushButton_sign,&QPushButton::clicked,this,&newCheck::slotOnSignButton);
    connect(ui->verticalScrollBar,&QScrollBar::valueChanged,ui->label_screenshot,&screenshotLabel::changeScreenshot);
    connect(ui->pushButton_save,&QPushButton::clicked,this,&newCheck::slotOnSaveButton);
    connect(ui->pushButton_deleteAll,&QPushButton::clicked,this,&newCheck::slotOnDeleteAllButton);
    connect(ui->pushButton_export,&QPushButton::clicked,this,&newCheck::slotOnExportButton);

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
    QString filePath = "output.pdf";
    QFile::remove(filePath);
    delete ui;
}

void newCheck::slotOnClearButton(){
    commandManager::getInstance()->screenshots.clear();
    commandManager::getInstance()->headlines.clear();
    updateScreenshots();
}

void newCheck::slotOnDeleteButton(){
    if(!commandManager::getInstance()->screenshots.isEmpty()){
        commandManager::getInstance()->screenshotValue = ui->verticalScrollBar->value();
        commandManager::getInstance()->screenshots.takeAt(commandManager::getInstance()->screenshotValue);
        commandManager::getInstance()->headlines.takeAt(commandManager::getInstance()->screenshotValue);
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
        //w->setCheck(this);
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
    //w->setCheck(this);
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
    //ui->label_current->setText(currentTime);
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
    //myInfo.basicInfo = ui->label_basic->text();
    myInfo.topic = ui->label_topic->text();
    //myInfo.checkMan = ui->label_name->text();
    myInfo.checkTime = ui->label_time->text();
    myInfo.screenshots = commandManager::getInstance()->screenshots;
    myInfo.illustrate = ui->textEdit->toPlainText();
}

void newCheck::slotOnExportButton(){
    QString filePath = QFileDialog::getSaveFileName(this, "Export PDF", QDir::homePath(), "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }
    generatePDF(filePath);
}

void newCheck::updateScreenshots(){
    ui->verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    QPixmap screenshot;
    if(commandManager::getInstance()->screenshots.size() == 0){
        ui->label_screenshot->setText("未有截图");
        ui->label_headline->setText("");
    }else{
        screenshot = commandManager::getInstance()->screenshots.at(commandManager::getInstance()->screenshotValue).scaled(ui->label_screenshot->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->label_screenshot->setPixmap(screenshot);
        ui->label_headline->setText(commandManager::getInstance()->headlines.at(commandManager::getInstance()->screenshotValue));
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

void newCheck::generatePDF(QString filePath){
    Q_UNUSED(filePath);
    /*
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPageLayout pageLayout = printer.pageLayout();
    QMarginsF margins(30, 30, 30, 30); // 设置页边距，单位为毫米
    pageLayout.setMargins(margins);

    QFont font("Arial",12);

    QPainter painter;
    if(painter.begin(&printer)){
        painter.setFont(font);

        int x = 100;
        int y = 100;
        //QString text = ui->label_basic->text();
        QRect textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()), Qt::AlignLeft, text);
        x = x + textRect.width() + 100;
        //text = ui->label_info->text();
        textRect = painter.fontMetrics().boundingRect(text);
        //painter. drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

        x = 100;
        y = y + textRect.height() + 50;
        //text = ui->label_topic->text();
        textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);
        x = x + textRect.width() + 100;
        //text = ui->lineEdit_topic->text();
        textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

        x = 100;
        y = y + textRect.height() + 250;
        //text = ui->label_check->text();
        textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);
        x = x + textRect.width() + 100;
        //text = ui->label_name->text();
        textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

        x = x + textRect.width() + 500;
        //text = ui->label_time->text();
        textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);
        x = x + textRect.width() + 100;
        //text = ui->label_current->text();
        textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

        x = 100;
        y = y + textRect.height() + 600;
        foreach(QPixmap pixmap,commandManager::getInstance()->screenshots){
            int ratioWid = printer.pageRect().width()/pixmap.width();
            int ratioHei = (printer.pageRect().height() - y)/pixmap.height();
            int ratio = std::min(ratioHei,ratioWid);
            QRect pixmapRect = QRect(x,y,pixmap.width() * ratio,pixmap.height() * ratio);
            painter.drawPixmap(pixmapRect,pixmap);
            y =  y + pixmap.height() * ratio + 300;
            if(y >= printer.pageRect().height()){
                printer.newPage();
                y = 100;
            }
        }

        if(!ui->textEdit->toPlainText().isEmpty()){
            text = ui->label->text();
            textRect = painter.fontMetrics().boundingRect(text);
            if(y + textRect.height() > printer.pageRect().height()){
                printer.newPage();
                y = 100;
            }
            //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

            y = y + textRect.height() + 300;
            //text = ui->textEdit->toPlainText();
            //QStringList lines = text.split("\n");
            QFontMetrics metrics(painter.font());
            int lineHeight = metrics.height();
            for(const QString& line : lines){
                QStringList words = line.split("");
                QString currentLine;
                for(const QString& word : words){
                    int width = metrics.horizontalAdvance(currentLine + word + " ");
                    if(width > printer.pageRect().width()){
                        if(y + lineHeight >= printer.pageRect().height()){
                            y = 100;
                            printer.newPage();
                        }
                        painter.drawText(x,y,printer.pageRect().width(),lineHeight,Qt::AlignLeft,currentLine);
                        y = y + lineHeight + 100;
                        currentLine.clear();
                    }
                    currentLine += word;
                }

                if(!currentLine.isEmpty()){
                    if(y + lineHeight >= printer.pageRect().height()){
                        y = 100;
                        printer.newPage();
                    }
                    painter.drawText(x,y,printer.pageRect().width(),lineHeight,Qt::AlignLeft,currentLine);
                    y = y + lineHeight + 100;
                }
            }
        }

        if(!ui->pushButton_sign->isEnabled()){
            text = "签字:";
            textRect = painter.fontMetrics().boundingRect(text);
            if(y + textRect.height() >= printer.pageRect().height()){
                printer.newPage();
                y = 100;
            }
            painter.drawText(x,y,textRect.width(),textRect.height(),Qt::AlignLeft,text);

            y = y + textRect.height() + 300;
            QPixmap sign;
            if(sign.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg") && !ui->pushButton_sign->isEnabled()){
                QRect pixmapRect = QRect(x,y,sign.width(),sign.height());
                if(y + pixmapRect.height() >= printer.pageRect().height()){
                    y = 100;
                    printer.newPage();
                }
                painter.drawPixmap(pixmapRect,sign);
            }
        }

        painter.end();
    }
    */
}

void newCheck::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        slotOnDeleteAllButton();
    }
}
