#include "check.h"

#include <QCoreApplication>
#include <QThread>
#include <QDateTime>
#include <QFileDialog>
#include <QPrinter>
#include <QMessageBox>

#include "commandmanager.h"
#include "screenshotview.h"

check::check(QWidget *parent)
    : UiMainWindow(parent)
{
    //设置无边框
    //FramelessHelper* helper = this->framelessHelper();
    //设置样式
    this->setStyle(UiMainWindow::UiStyle::Light);
    //设置标题
    setWindowTitle("校核");
    //设置字体
    QFont font;
    font.setFamily("思源黑体");
    font.setPixelSize(13);
    this->setTitleFont(font);
    setFixedSize(631,773);

    QIcon mainIcon(":/icons/newCheck/main.png");
    setWindowIcon(mainIcon);

    setupWidgets(this);

    label_screenshot->label_headline = label_headline;
    label_screenshot->verticalScrollBar = verticalScrollBar;

    QIcon beginScreenshot(":/icons/newCheck/beginScreenshot.png");
    pushButton_begin->setIcon(beginScreenshot);
    pushButton_begin->setToolTip("开始截图");

    QIcon deleteScreenshot(":/icons/newCheck/delete.png");
    pushButton_delete->setIcon(deleteScreenshot);
    pushButton_delete->setToolTip("删除截图");

    QIcon replaceScreenshot(":/icons/newCheck/replace.png");
    pushButton_re->setIcon(replaceScreenshot);
    pushButton_re->setToolTip("重新截图");

    QIcon clearScreenshot(":/icons/newCheck/clear.png");
    pushButton_clear->setIcon(clearScreenshot);
    pushButton_clear->setToolTip("清空截图");

    //截图显示
    label_screenshot->setText("未有截图");

    //拉动条
    QString styleSheet = "QScrollBar { background-color: gray; }";
    verticalScrollBar->setStyleSheet(styleSheet);
    verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    verticalScrollBar->setPageStep(1);

    connect(pushButton_begin,&QPushButton::clicked,this,&check::slotOnBeginButton);
    connect(pushButton_delete,&QPushButton::clicked,this,&check::slotOnDeleteButton);
    connect(pushButton_re,&QPushButton::clicked,this,&check::slotOnReButton);
    connect(pushButton_clear,&QPushButton::clicked,this,&check::slotOnClearButton);
    connect(verticalScrollBar,&QScrollBar::valueChanged,label_screenshot,&screenshotLabel::changeScreenshot);
    connect(pushButton_sign,&QPushButton::clicked,this,&check::slotOnSignButton);
    connect(pushButton_export,&QPushButton::clicked,this,&check::slotOnExportButton);
    connect(pushButton_deleteAll,&QPushButton::clicked,this,&check::slotOnDeleteAllButton);
}

check::~check(){
    QString filePath = "output.pdf";
    QFile::remove(filePath);
}

void check::setupWidgets(UiMainWindow *newCheck){
    if (newCheck->objectName().isEmpty())
        newCheck->setObjectName(QString::fromUtf8("newCheck"));
    QWidget* widget = new QWidget;
    verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    widget->setLayout(verticalLayout);
    newCheck->setCentralWidget(widget);

    //基本信息
    label_info = new QLabel(widget);
    label_info->setObjectName(QString::fromUtf8("label_info"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label_info->sizePolicy().hasHeightForWidth());
    label_info->setSizePolicy(sizePolicy);
    QFont font;
    font.setPointSize(9);
    label_info->setFont(font);
    label_info->setScaledContents(true);
    label_info->setWordWrap(false);

    verticalLayout->addWidget(label_info);

    //主题和输入栏
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_topic = new QLabel(widget);
    label_topic->setObjectName(QString::fromUtf8("label_topic"));
    label_topic->setFont(font);

    horizontalLayout->addWidget(label_topic);

    lineEdit_topic = new QLineEdit(widget);
    lineEdit_topic->setObjectName(QString::fromUtf8("lineEdit_topic"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(lineEdit_topic->sizePolicy().hasHeightForWidth());
    lineEdit_topic->setSizePolicy(sizePolicy1);

    horizontalLayout->addWidget(lineEdit_topic);


    verticalLayout->addLayout(horizontalLayout);

    //spacer和签字图片
    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_6->addItem(horizontalSpacer);

    label_sign = new QLabel(widget);
    label_sign->setObjectName(QString::fromUtf8("label_sign"));
    QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(label_sign->sizePolicy().hasHeightForWidth());
    label_sign->setSizePolicy(sizePolicy2);
    label_sign->setFixedSize(QSize(200,60));
    label_sign->setLayoutDirection(Qt::LeftToRight);
    label_sign->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    horizontalLayout_6->addWidget(label_sign);


    verticalLayout->addLayout(horizontalLayout_6);

    //校核人和校核时间
    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label_check = new QLabel(widget);
    label_check->setObjectName(QString::fromUtf8("label_check"));

    horizontalLayout_3->addWidget(label_check);

    label_time = new QLabel(widget);
    label_time->setObjectName(QString::fromUtf8("label_time"));

    horizontalLayout_3->addWidget(label_time);


    verticalLayout->addLayout(horizontalLayout_3);

    //四个截图功能按钮
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    pushButton_begin = new QPushButton(widget);
    pushButton_begin->setObjectName(QString::fromUtf8("pushButton_begin"));

    horizontalLayout_2->addWidget(pushButton_begin);

    pushButton_delete = new QPushButton(widget);
    pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));

    horizontalLayout_2->addWidget(pushButton_delete);

    pushButton_re = new QPushButton(widget);
    pushButton_re->setObjectName(QString::fromUtf8("pushButton_re"));

    horizontalLayout_2->addWidget(pushButton_re);

    pushButton_clear = new QPushButton(widget);
    pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

    horizontalLayout_2->addWidget(pushButton_clear);


    verticalLayout->addLayout(horizontalLayout_2);

    //截图标题
    label_headline = new QLabel(widget);
    label_headline->setObjectName(QString::fromUtf8("label_headline"));

    verticalLayout->addWidget(label_headline);

    //展示截图和滑动条
    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    label_screenshot = new screenshotLabel(widget);
    label_screenshot->setObjectName(QString::fromUtf8("label_screenshot"));
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(label_screenshot->sizePolicy().hasHeightForWidth());
    label_screenshot->setSizePolicy(sizePolicy3);
    QFont font1;
    font1.setFamily(QString::fromUtf8("Bahnschrift SemiLight"));
    font1.setPointSize(40);
    font1.setBold(true);
    font1.setItalic(true);
    font1.setUnderline(true);
    font1.setWeight(75);
    label_screenshot->setFont(font1);
    label_screenshot->setAlignment(Qt::AlignCenter);

    horizontalLayout_4->addWidget(label_screenshot);

    verticalScrollBar = new QScrollBar(widget);
    verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
    verticalScrollBar->setOrientation(Qt::Vertical);

    horizontalLayout_4->addWidget(verticalScrollBar);


    verticalLayout->addLayout(horizontalLayout_4);

    //QLabel显示 "校核说明"
    label = new QLabel(widget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setMaximumSize(QSize(16777215, 30));

    verticalLayout->addWidget(label);

    //校核说明输入栏
    textEdit = new QTextEdit(widget);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
    textEdit->setSizePolicy(sizePolicy4);
    textEdit->setMaximumSize(QSize(16777215, 100));

    verticalLayout->addWidget(textEdit);

    //四个功能按钮
    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    pushButton_sign = new QPushButton(widget);
    pushButton_sign->setObjectName(QString::fromUtf8("pushButton_sign"));
    pushButton_sign->setMaximumSize(QSize(16777215, 40));

    horizontalLayout_5->addWidget(pushButton_sign);

    pushButton_export = new QPushButton(widget);
    pushButton_export->setObjectName(QString::fromUtf8("pushButton_export"));
    pushButton_export->setEnabled(true);
    QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(pushButton_export->sizePolicy().hasHeightForWidth());
    pushButton_export->setSizePolicy(sizePolicy5);
    pushButton_export->setMaximumSize(QSize(200, 40));

    horizontalLayout_5->addWidget(pushButton_export);

    pushButton_deleteAll = new QPushButton(widget);
    pushButton_deleteAll->setObjectName(QString::fromUtf8("pushButton_deleteAll"));
    pushButton_deleteAll->setMaximumSize(QSize(16777215, 40));

    horizontalLayout_5->addWidget(pushButton_deleteAll);

    pushButton_save = new QPushButton(widget);
    pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
    pushButton_save->setMaximumSize(QSize(16777215, 40));

    horizontalLayout_5->addWidget(pushButton_save);


    verticalLayout->addLayout(horizontalLayout_5);


    retranslateUi();

    QMetaObject::connectSlotsByName(newCheck);
}

void check::retranslateUi(){
    label_info->setText(QCoreApplication::translate("newCheck", "\345\237\272\346\234\254\344\277\241\346\201\257\357\274\232 xxx\351\241\271\347\233\256\345\220\215\347\247\260 + \342\200\234\351\241\271\347\233\256\346\240\241\346\240\270\345\215\225-\342\200\235+\342\200\234\347\274\226\347\240\201QUUID\342\200\235", nullptr));
    label_topic->setText(QCoreApplication::translate("newCheck", "\344\270\273\351\242\230\357\274\232 ", nullptr));
    pushButton_begin->setText(QString());
    pushButton_delete->setText(QString());
    pushButton_re->setText(QString());
    pushButton_clear->setText(QString());
    label_sign->setText(QString());
    label_check->setText(QCoreApplication::translate("newCheck", "\346\240\241\346\240\270\344\272\272\357\274\232name", nullptr));
    label_time->setText(QCoreApplication::translate("newCheck", "\346\240\241\346\240\270\346\227\266\351\227\264\357\274\232", nullptr));
    label_headline->setText(QString());
    label_screenshot->setText(QString());
    label->setText(QCoreApplication::translate("newCheck", "\346\240\241\346\240\270\350\257\264\346\230\216\357\274\232", nullptr));
    pushButton_sign->setText(QCoreApplication::translate("newCheck", "\347\255\276\345\255\227", nullptr));
    pushButton_export->setText(QCoreApplication::translate("newCheck", "\345\257\274\345\207\272", nullptr));
    pushButton_deleteAll->setText(QCoreApplication::translate("newCheck", "\345\217\226\346\266\210", nullptr));
    pushButton_save->setText(QCoreApplication::translate("newCheck", "\347\241\256\345\256\232", nullptr));
}

void check::slotOnBeginButton(){
    showMinimized();
    QThread::msleep(250);
    screenshotView* w = screenshotView::getInstance();
    commandManager::getInstance()->screenshotValue = verticalScrollBar->value();
    w->setType(shotType::newShot);
    w->setCheck(this);
    w->setWindowState(Qt::WindowActive);
    w->show();
}

void check::updateScreenshots(){
    verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    QPixmap screenshot;
    if(commandManager::getInstance()->screenshots.size() == 0){
        label_screenshot->setText("未有截图");
        label_headline->setText("");
    }else{
        screenshot = commandManager::getInstance()->screenshots.at(commandManager::getInstance()->screenshotValue).scaled(label_screenshot->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        label_screenshot->setPixmap(screenshot);
        label_headline->setText(commandManager::getInstance()->headlines.at(commandManager::getInstance()->screenshotValue));
    }
}

void check::slotOnDeleteButton(){
    if(!commandManager::getInstance()->screenshots.isEmpty()){
        commandManager::getInstance()->screenshotValue = verticalScrollBar->value();
        commandManager::getInstance()->screenshots.takeAt(commandManager::getInstance()->screenshotValue);
        commandManager::getInstance()->headlines.takeAt(commandManager::getInstance()->screenshotValue);
        if(commandManager::getInstance()->screenshotValue >= 1){
            commandManager::getInstance()->screenshotValue -= 1;
            verticalScrollBar->setValue(commandManager::getInstance()->screenshotValue);
        }
        updateScreenshots();
    }
}

void check::slotOnReButton(){
    if(!commandManager::getInstance()->screenshots.isEmpty()){
        showMinimized();
        QThread::msleep(250);
        screenshotView* w = screenshotView::getInstance();
        commandManager::getInstance()->screenshotValue = verticalScrollBar->value();
        w->setType(shotType::replace);
        w->setCheck(this);
        w->setWindowState(Qt::WindowActive);
        w->show();
    }
}

void check::slotOnClearButton(){
    commandManager::getInstance()->screenshots.clear();
    commandManager::getInstance()->headlines.clear();
    updateScreenshots();
}

void check::slotOnSignButton(){
    QPixmap sign;
    if(sign.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg")){
        label_sign->setPixmap(sign);
        label_sign->setScaledContents(true);
    }

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    label_time->setText(label_time->text() + currentTime);
    pushButton_sign->setEnabled(false);
    pushButton_re->setEnabled(false);
    pushButton_begin->setEnabled(false);
    pushButton_delete->setEnabled(false);
    pushButton_clear->setEnabled(false);
    lineEdit_topic->setEnabled(false);
    textEdit->setEnabled(false);
}

void check::slotOnExportButton(){
    QString filePath = QFileDialog::getSaveFileName(this, "Export PDF", QDir::homePath(), "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }
    generatePDF(filePath);
}

void check::slotOnDeleteAllButton(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"confirmation","Are you sure you want to delete?",QMessageBox::Yes | QMessageBox::No);
    messageBoxIsShowing = true;
    if(reply == QMessageBox::Yes){
        QWidget::close();
    }
    messageBoxIsShowing = false;
}

void check::generatePDF(QString filePath){
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
        QString text = label_info->text();
        QRect textRect = painter.fontMetrics().boundingRect(text);
        painter.drawText(QRect(x,y,textRect.width(),textRect.height()), Qt::AlignLeft, text);
        x = x + textRect.width() + 100;
        //text = ui->label_info->text();
        //textRect = painter.fontMetrics().boundingRect(text);
        //painter. drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

        x = 100;
        y = y + textRect.height() + 50;
        text = label_topic->text();
        textRect = painter.fontMetrics().boundingRect(text);
        painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);
        x = x + textRect.width() + 100;
        text = lineEdit_topic->text();
        textRect = painter.fontMetrics().boundingRect(text);
        painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

        x = 100;
        y = y + textRect.height() + 250;
        text = label_check->text();
        textRect = painter.fontMetrics().boundingRect(text);
        painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);
        //x = x + textRect.width() + 100;
        //text = label_name->text();
        //textRect = painter.fontMetrics().boundingRect(text);
        //painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

        x = x + textRect.width() + 500;
        text = label_time->text();
        textRect = painter.fontMetrics().boundingRect(text);
        painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);
        //x = x + textRect.width() + 100;
        //text = label_current->text();
        //textRect = painter.fontMetrics().boundingRect(text);
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

        if(!textEdit->toPlainText().isEmpty()){
            text = label->text();
            textRect = painter.fontMetrics().boundingRect(text);
            if(y + textRect.height() > printer.pageRect().height()){
                printer.newPage();
                y = 100;
            }
            painter.drawText(QRect(x,y,textRect.width(),textRect.height()),Qt::AlignLeft,text);

            y = y + textRect.height() + 300;
            text = textEdit->toPlainText();
            QStringList lines = text.split("\n");
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

        if(!pushButton_sign->isEnabled()){
            text = "签字:";
            textRect = painter.fontMetrics().boundingRect(text);
            if(y + textRect.height() >= printer.pageRect().height()){
                printer.newPage();
                y = 100;
            }
            painter.drawText(x,y,textRect.width(),textRect.height(),Qt::AlignLeft,text);

            y = y + textRect.height() + 300;
            QPixmap sign;
            if(sign.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg") && !pushButton_sign->isEnabled()){
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
}


void check::closeEvent(QCloseEvent *event)
{
    if(messageBoxIsShowing){
        event->accept();
    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"confirmation","Are you sure you want to delete?",QMessageBox::Yes | QMessageBox::No);
        messageBoxIsShowing = true;
        if(reply == QMessageBox::Yes){
            event->accept();
        }else{
            event->ignore();
        }
        messageBoxIsShowing = false;
    }
}
