#include "check.h"

#include <QCoreApplication>
#include <QThread>
#include <QDateTime>
#include <QFileDialog>
#include <QPrinter>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>

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
    resize(631,773);

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
    connect(pushButton_preview,&QPushButton::clicked,this,&check::slotOnPreviewButton);
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

    pushButton_preview = new QPushButton(widget);
    pushButton_preview->setObjectName(QString::fromUtf8("pushButton_preview"));
    pushButton_preview->setMaximumSize(QSize(16777215,40));
    pushButton_preview->setText("预览");

    horizontalLayout_5->addWidget(pushButton_preview);

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
    //创建打印机对象
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter;
    if(painter.begin(&printer)){
        //painter.setPen(Qt::black);
        painter.setPen(QPen(Qt::black,5));
        QRect myPageRect = QRect(167,167,9350,13450);

        QString title = "my title";
        QFont titleFont("思源黑体", 20, QFont::Bold);
        painter.setFont(titleFont);
        painter.drawText(myPageRect,Qt::AlignHCenter,title);
        int titleHeight = painter.fontMetrics().boundingRect(title).height() + 20;
        myPageRect = QRect(myPageRect.x(),myPageRect.y() + titleHeight,myPageRect.width(),myPageRect.height() - titleHeight);

        painter.drawLine(QLine(myPageRect.x(),myPageRect.y(),myPageRect.x() + myPageRect.width(),myPageRect.y()));
        myPageRect = QRect(myPageRect.x(),myPageRect.y() + 20,myPageRect.width(),myPageRect.height() - 20);

        if(!lineEdit_topic->text().isEmpty()){
            QFont contentFont("思源黑体",12,QFont::Normal);
            painter.setFont(contentFont);
            QString topic = "主题： " + lineEdit_topic->text();
            painter.drawText(myPageRect,Qt::AlignLeft,topic);;
            int topicHeight = painter.fontMetrics().boundingRect(topic).height() + 20;
            myPageRect = QRect(myPageRect.x(),myPageRect.y() + topicHeight,myPageRect.width(),myPageRect.height() - topicHeight);
        }else{
            QFont contentFont("思源黑体",12,QFont::Normal);
            painter.setFont(contentFont);
            QString topic = "主题：未输入主题";
            painter.save();
            painter.setPen(Qt::red);
            painter.drawText(myPageRect,Qt::AlignLeft,topic);
            painter.restore();
            int topicHeight = painter.fontMetrics().boundingRect(topic).height() + 20;
            myPageRect = QRect(myPageRect.x(),myPageRect.y() + topicHeight,myPageRect.width(),myPageRect.height() - topicHeight);
        }

        QPixmap signPixmap;
        if(pushButton_sign->isEnabled()){
            painter.save();
            painter.setPen(Qt::red);
            QString sign = "签字：未签字";
            painter.drawText(myPageRect,Qt::AlignLeft,sign);
            painter.restore();
            int signHeight = painter.fontMetrics().boundingRect(sign).height() + 20;
            myPageRect = QRect(myPageRect.x(),myPageRect.y() + signHeight,myPageRect.width(),myPageRect.height() - signHeight);
        }else if(signPixmap.load("C:\\Users\\drink water\\Pictures\\微信头像.jpg")){
            QString sign = "签字：";
            painter.drawText(myPageRect,Qt::AlignLeft,sign);
            int signWidth = painter.fontMetrics().boundingRect(sign).width() + 20;
            QRect pixmapRect = QRect(myPageRect.x() + signWidth,myPageRect.y(),signPixmap.width(),signPixmap.height());
            painter.drawPixmap(pixmapRect,signPixmap);
            myPageRect = QRect(myPageRect.x(),myPageRect.y() + signPixmap.height(),myPageRect.width(),myPageRect.height() - signPixmap.height());
        }

        QString man = label_check->text();
        painter.drawText(myPageRect,Qt::AlignLeft,man);
        int manHeight = painter.fontMetrics().boundingRect(man).height() + 20;
        myPageRect = QRect(myPageRect.x(),myPageRect.y() + manHeight,myPageRect.width(),myPageRect.height() - manHeight);

        QString date = label_time->text();
        painter.drawText(myPageRect,Qt::AlignLeft,date);
        int dateHeight = painter.fontMetrics().boundingRect(date).height() + 20;
        myPageRect = QRect(myPageRect.x(),myPageRect.y() + dateHeight,myPageRect.width(),myPageRect.height() - dateHeight);

        painter.drawLine(QLine(myPageRect.x(),myPageRect.y(),myPageRect.x() + myPageRect.width(),myPageRect.y()));
        myPageRect = QRect(myPageRect.x(),myPageRect.y() + 20,myPageRect.width(),myPageRect.height() - 20);

        if(textEdit->toPlainText().isEmpty()){
            painter.save();
            painter.setPen(Qt::red);
            QString illustrate = label->text() + "无校核说明";
            painter.drawText(myPageRect,Qt::AlignLeft,illustrate);
            painter.restore();
            int illustrateHeight = painter.fontMetrics().boundingRect(illustrate).height();
            myPageRect = QRect(myPageRect.x(),myPageRect.y() + illustrateHeight,myPageRect.width(),myPageRect.height() - illustrateHeight);
        }else{
            QString illustrate = label->text();
            painter.drawText(myPageRect,Qt::AlignLeft,illustrate);
            int illustrateHeight = painter.fontMetrics().boundingRect(illustrate).height();
            myPageRect = QRect(myPageRect.x(),myPageRect.y() + illustrateHeight,myPageRect.width(),myPageRect.height() - illustrateHeight);

            QString text = textEdit->toPlainText();
            QStringList lines = text.split("\n");
            QFontMetrics metrics(painter.font());
            int lineHeight = metrics.height();
            for(const QString& line : lines){
                QStringList words = line.split("");
                QString currentLine;
                for(const QString& word : words){
                    int width = metrics.horizontalAdvance(currentLine + word + " ");
                    if(width > myPageRect.width()){
                        if(myPageRect.y() + lineHeight >= myPageRect.height()){
                            printer.newPage();
                            myPageRect = QRect(167,167,9350,13450);
                        }
                        painter.drawText(myPageRect,Qt::AlignLeft,currentLine);
                        myPageRect = QRect(myPageRect.x(),myPageRect.y() + lineHeight,myPageRect.width(),myPageRect.height() - lineHeight);
                        currentLine.clear();
                    }
                    currentLine += word;
                }

                if(!currentLine.isEmpty()){
                    if(myPageRect.y() + lineHeight >= printer.pageRect().height()){
                        myPageRect = QRect(167,167,9350,13450);
                        printer.newPage();
                    }
                    painter.drawText(myPageRect,Qt::AlignLeft,currentLine);
                    myPageRect = QRect(myPageRect.x(),myPageRect.y() + lineHeight,myPageRect.width(),myPageRect.height() - lineHeight);
                }
            }
        }

        int quantity = 0;
        foreach(QPixmap screenshot,commandManager::getInstance()->screenshots){
            myPageRect = QRect(167,167,9350,13450);
            if(quantity == 0){
                printer.newPage();
                painter.save();
                painter.setPen(QPen(Qt::black,20));
                painter.drawRect(myPageRect);
                painter.drawLine(QLineF(myPageRect.x(),myPageRect.y() + myPageRect.height()/2,myPageRect.right(),myPageRect.y() + myPageRect.height()/2));
                painter.restore();

                myPageRect = QRect(myPageRect.x(),myPageRect.y(),myPageRect.width(),myPageRect.height()/2);
                QString info = "截图说明" + QString::number(commandManager::getInstance()->screenshots.indexOf(screenshot));
                painter.drawText(myPageRect,Qt::AlignLeft,info);
                int infoHeight = painter.fontMetrics().boundingRect(info).height();
                myPageRect = QRect(myPageRect.x(),myPageRect.y() + infoHeight,myPageRect.width(),myPageRect.height()-infoHeight);

                QSize screenshotSize = screenshot.size();
                qreal scaleX = static_cast<qreal>(myPageRect.width()) / screenshotSize.width();
                qreal scaleY = static_cast<qreal>(myPageRect.height()) / screenshotSize.height();
                qreal scale = qMin(scaleX, scaleY);

                int scaledWidth = static_cast<int>(screenshotSize.width() * scale);
                int scaledHeight = static_cast<int>(screenshotSize.height() * scale);

                int x = myPageRect.x() + (myPageRect.width() - scaledWidth) / 2;
                int y = myPageRect.y() + (myPageRect.height() - scaledHeight) / 2;

                //painter.drawPixmap(myPageRect,screenshot);
                painter.drawPixmap(x,y,scaledWidth,scaledHeight,screenshot);
                quantity ++;
            }else{
                myPageRect = QRect(myPageRect.x(),myPageRect.y() + myPageRect.height()/2,myPageRect.width(),myPageRect.height()/2);
                QString info = "截图说明" + QString::number(commandManager::getInstance()->screenshots.lastIndexOf(screenshot));
                painter.drawText(myPageRect,Qt::AlignLeft,info);
                int infoHeight = painter.fontMetrics().boundingRect(info).height();
                myPageRect = QRect(myPageRect.x(),myPageRect.y() + infoHeight,myPageRect.width(),myPageRect.height() - infoHeight);

                QSize screenshotSize = screenshot.size();
                qreal scaleX = static_cast<qreal>(myPageRect.width()) / screenshotSize.width();
                qreal scaleY = static_cast<qreal>(myPageRect.height()) / screenshotSize.height();
                qreal scale = qMin(scaleX, scaleY);

                int scaledWidth = static_cast<int>(screenshotSize.width() * scale);
                int scaledHeight = static_cast<int>(screenshotSize.height() * scale);

                int x = myPageRect.x() + (myPageRect.width() - scaledWidth) / 2;
                int y = myPageRect.y() + (myPageRect.height() - scaledHeight) / 2;

                //painter.drawPixmap(myPageRect,screenshot);
                painter.drawPixmap(x,y,scaledWidth,scaledHeight,screenshot);
                quantity = 0;
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

void check::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    int currentImageIndex = commandManager::getInstance()->screenshots.size() - 1;
    label_screenshot->changeScreenshot(currentImageIndex);
}

void check::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        slotOnDeleteAllButton();
    }
}

void check::slotOnPreviewButton(){
    QString filePath = "preview.pdf";

    generatePDF(filePath);

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}





