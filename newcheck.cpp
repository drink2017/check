#include "newcheck.h"

#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <QDateTime>

#include "screenshotview.h"
#include "commandmanager.h"

newCheck::newCheck()
{
    //设置样式
    this->setStyle(UiMainWindow::UiStyle::Light);
    //设置标题
    setWindowTitle("校核");
    //设置字体
    QFont font;
    font.setFamily("思源黑体");
    font.setPixelSize(13);
    this->setTitleFont(font);

    setStyleSheet("QWidget#ShadowWidget{\
                                       background-color: #00FFFF;\
                                       border-radius: 20px;}");

    QIcon mainIcon(":/icons/newCheck/main.png");
    setWindowIcon(mainIcon);

    setupWidgets(this);

    label_5->label_headline = label_2;
    label_5->verticalScrollBar = verticalScrollBar;
    label_5->listWidget = listWidget;
    label_5->illustrate = textEdit;

    QIcon beginScreenshot(":/icons/newCheck/beginScreenshot.png");
    pushButton->setIcon(beginScreenshot);
    pushButton->setToolTip("开始截图");

    QIcon deleteScreenshot(":/icons/newCheck/delete.png");
    pushButton_3->setIcon(deleteScreenshot);
    pushButton_3->setToolTip("删除截图");

    QIcon replaceScreenshot(":/icons/newCheck/replace.png");
    pushButton_2->setIcon(replaceScreenshot);
    pushButton_2->setToolTip("重新截图");

    QIcon clearScreenshot(":/icons/newCheck/clear.png");
    pushButton_4->setIcon(clearScreenshot);
    pushButton_4->setToolTip("清空截图");

    //截图显示
    label_5->setText("未有截图");

    //拉动条
    QString styleSheet = "QScrollBar { background-color: gray; }";
    label_5->verticalScrollBar->setStyleSheet(styleSheet);
    label_5->verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    label_5->verticalScrollBar->setPageStep(1);

    connect(pushButton,&QPushButton::clicked,this,&newCheck::slotOnBeginButton);
    connect(pushButton_3,&QPushButton::clicked,this,&newCheck::slotOnDeleteButton);
    connect(pushButton_2,&QPushButton::clicked,this,&newCheck::slotOnReButton);
    connect(pushButton_4,&QPushButton::clicked,this,&newCheck::slotOnClearButton);
    connect(verticalScrollBar,&QScrollBar::valueChanged,label_5,&screenshotLabel::changeScreenshot);
    connect(pushButton_6,&QPushButton::clicked,this,&newCheck::slotOnSignButton);
    //connect(pushButton_5,&QPushButton::clicked,this,&check::slotOnPreviewButton);
    //connect(pushButton_7,&QPushButton::clicked,this,&check::slotOnExportButton);
    connect(pushButton_9,&QPushButton::clicked,this,&newCheck::slotOnDeleteAllButton);
    connect(listWidget,&QListWidget::itemSelectionChanged,this,&newCheck::slotOnListItemSelection);
    connect(textEdit,&QTextEdit::textChanged,this,&newCheck::slotOnTextChanged);
}

void newCheck::setupWidgets(UiMainWindow *Widget){
    if (Widget->objectName().isEmpty())
        Widget->setObjectName(QString::fromUtf8("Widget"));
    QWidget* widget = new QWidget;
    Widget->resize(800, 600);
    verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    Widget->setCentralWidget(widget);
    label = new QLabel(widget);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout->addWidget(label);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_3 = new QLabel(widget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout->addWidget(label_3);

    lineEdit = new QLineEdit(widget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    horizontalLayout->addWidget(lineEdit);


    verticalLayout->addLayout(horizontalLayout);

    //校核人和校核时间
    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    label_4 = new QLabel(widget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_5->addWidget(label_4);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer_3);

    label_6 = new QLabel(widget);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout_5->addWidget(label_6);


    verticalLayout->addLayout(horizontalLayout_5);

    line = new QFrame(widget);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    verticalLayout->addWidget(line);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    pushButton = new QPushButton(widget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    horizontalLayout_2->addWidget(pushButton);

    pushButton_2 = new QPushButton(widget);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    horizontalLayout_2->addWidget(pushButton_2);

    pushButton_3 = new QPushButton(widget);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

    horizontalLayout_2->addWidget(pushButton_3);

    pushButton_4 = new QPushButton(widget);
    pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

    horizontalLayout_2->addWidget(pushButton_4);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    label_2 = new QLabel(widget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_2->addWidget(label_2);


    verticalLayout->addLayout(horizontalLayout_2);

    line_2 = new QFrame(widget);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);

    verticalLayout->addWidget(line_2);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    listWidget = new QListWidget(widget);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
    listWidget->setSizePolicy(sizePolicy);
    listWidget->setViewMode(QListView::IconMode);

    horizontalLayout_3->addWidget(listWidget);

    label_5 = new screenshotLabel(widget);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Bahnschrift SemiLight"));
    font1.setPointSize(40);
    font1.setBold(true);
    font1.setItalic(true);
    font1.setUnderline(true);
    font1.setWeight(75);
    label_5->setFont(font1);
    label_5->setAlignment(Qt::AlignCenter);

    QSizePolicy labelPolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label_5->setSizePolicy(labelPolicy);

    horizontalLayout_3->addWidget(label_5);

    verticalScrollBar = new QScrollBar(widget);
    verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
    verticalScrollBar->setOrientation(Qt::Vertical);

    horizontalLayout_3->addWidget(verticalScrollBar);

    textEdit = new QTextEdit(widget);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setEnabled(false);

    horizontalLayout_3->addWidget(textEdit);

    horizontalLayout_3->setStretch(0, 1);
    horizontalLayout_3->setStretch(1, 4);
    horizontalLayout_3->setStretch(3, 4);

    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    pushButton_5 = new QPushButton(widget);
    pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

    horizontalLayout_4->addWidget(pushButton_5);

    pushButton_6 = new QPushButton(widget);
    pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

    horizontalLayout_4->addWidget(pushButton_6);

    pushButton_7 = new QPushButton(widget);
    pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

    horizontalLayout_4->addWidget(pushButton_7);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_4->addItem(horizontalSpacer_2);

    pushButton_9 = new QPushButton(widget);
    pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

    horizontalLayout_4->addWidget(pushButton_9);

    pushButton_8 = new QPushButton(widget);
    pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

    horizontalLayout_4->addWidget(pushButton_8);


    verticalLayout->addLayout(horizontalLayout_4);


    retranslateUi();

    QMetaObject::connectSlotsByName(Widget);
}

void newCheck::retranslateUi(){
    label->setText(QCoreApplication::translate("Widget", "\346\240\241\346\240\270\345\215\225:\350\216\267\345\217\226\346\234\254\350\212\202\347\202\271\346\211\200\345\234\250\351\241\271\347\233\256\347\232\204\351\241\271\347\233\256\345\220\215\347\247\260+UUID\347\274\226\347\240\201", nullptr));
    label_3->setText(QCoreApplication::translate("Widget", "\346\240\241\346\240\270\344\270\273\351\242\230:", nullptr));
    label_4->setText(QCoreApplication::translate("Widget", "\346\240\241\346\240\270\344\272\272:\350\216\267\345\217\226\346\234\254\350\212\202\347\202\271\346\211\200\345\261\236\344\272\272\345\220\215\345\255\227\347\232\204icon", nullptr));
    label_6->setText(QCoreApplication::translate("Widget", "\346\240\241\346\240\270\346\227\266\351\227\264:\350\216\267\345\217\226\347\202\271\345\207\273\347\255\276\345\255\227\347\232\204\347\263\273\347\273\237\346\227\266\351\227\264", nullptr));
    pushButton->setText(QCoreApplication::translate("Widget", "\346\210\252\345\233\276", nullptr));
    pushButton_2->setText(QCoreApplication::translate("Widget", "\351\207\215\346\210\252", nullptr));
    pushButton_3->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244", nullptr));
    pushButton_4->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
    label_2->setText(QCoreApplication::translate("Widget", "\345\275\223\345\211\215\351\241\265/\345\205\261\350\256\241\345\245\275\345\244\232\351\241\265", nullptr));
    label_5->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
    pushButton_5->setText(QCoreApplication::translate("Widget", "\351\242\204\350\247\210", nullptr));
    pushButton_6->setText(QCoreApplication::translate("Widget", "\347\255\276\345\255\227", nullptr));
    pushButton_7->setText(QCoreApplication::translate("Widget", "\345\257\274\345\207\272", nullptr));
    pushButton_9->setText(QCoreApplication::translate("Widget", "\345\217\226\346\266\210", nullptr));
    pushButton_8->setText(QCoreApplication::translate("Widget", "\347\241\256\345\256\232", nullptr));
}

void newCheck::slotOnBeginButton(){
    commandManager::getInstance()->checkIsMax = isMaximized();
    showMinimized();
    QThread::msleep(250);
    screenshotView* w = screenshotView::getInstance();
    commandManager::getInstance()->screenshotValue = verticalScrollBar->value();
    w->setType(shotType::newShot);
    w->setCheck(this);
    w->setWindowState(Qt::WindowActive);
    w->show();
}

void newCheck::slotOnReButton(){
    if(!commandManager::getInstance()->screenshots.isEmpty()){
        commandManager::getInstance()->checkIsMax = isMaximized();
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

void newCheck::slotOnDeleteButton(){
    if(!commandManager::getInstance()->screenshots.isEmpty()){
        textEdit->clear();
        commandManager::getInstance()->screenshotValue = verticalScrollBar->value();
        commandManager::getInstance()->screenshots.takeAt(commandManager::getInstance()->screenshotValue);
        commandManager::getInstance()->headlines.takeAt(commandManager::getInstance()->screenshotValue);
        commandManager::getInstance()->illustrate.takeAt(commandManager::getInstance()->screenshotValue);
        if(commandManager::getInstance()->screenshotValue >= 1){
            commandManager::getInstance()->screenshotValue -= 1;
            verticalScrollBar->setValue(commandManager::getInstance()->screenshotValue);
        }
        updateListWidget();
        updateScreenshots();
    }
}

void newCheck::slotOnClearButton(){
    if(!commandManager::getInstance()->screenshots.empty()){
        textEdit->clear();
        textEdit->setEnabled(false);
    }
    commandManager::getInstance()->screenshots.clear();
    commandManager::getInstance()->headlines.clear();
    commandManager::getInstance()->illustrate.clear();
    updateScreenshots();
    updateListWidget();
}

void newCheck::slotOnDeleteAllButton(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"confirmation","Are you sure you want to delete?",QMessageBox::Yes | QMessageBox::No);
    messageBoxIsShowing = true;
    if(reply == QMessageBox::Yes){
        QWidget::close();
    }
    messageBoxIsShowing = false;
}

void newCheck::slotOnSignButton(){
    QString name = "name";
    label_4->setText("校核人:" + name);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    label_6->setText("校核时间:" + currentTime);
    pushButton_6->setEnabled(false);
    pushButton->setEnabled(false);
    pushButton_2->setEnabled(false);
    pushButton_3->setEnabled(false);
    pushButton_4->setEnabled(false);
    lineEdit->setEnabled(false);
    textEdit->setEnabled(false);
}

void newCheck::updateScreenshots(){
    verticalScrollBar->setRange(0,commandManager::getInstance()->screenshots.size() - 1);
    QPixmap screenshot;
    if(commandManager::getInstance()->screenshots.size() == 0){
        label_5->setText("未有截图");
        label_2->setText("");
        textEdit->setEnabled(false);
    }else{
        screenshot = commandManager::getInstance()->screenshots.at(commandManager::getInstance()->screenshotValue).scaled(label_5->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        label_5->setPixmap(screenshot);
        label_2->setText(commandManager::getInstance()->headlines.at(commandManager::getInstance()->screenshotValue));
        textEdit->setText(commandManager::getInstance()->illustrate.at(commandManager::getInstance()->screenshotValue));
        textEdit->setEnabled(true);
        listWidget->setCurrentRow(verticalScrollBar->value());
    }
}

void newCheck::resizeEvent(QResizeEvent *event)
{
    int currentImageIndex = verticalScrollBar->value();
    label_5->changeScreenshot(currentImageIndex);
    updateListWidget();
    UiMainWindow::resizeEvent(event);
}

void newCheck::closeEvent(QCloseEvent *event)
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

void newCheck::updateListWidget(){
    listWidget->clear();
    for(QPixmap pixmapItem : commandManager::getInstance()->screenshots){
        QListWidgetItem* item = new QListWidgetItem(listWidget);
        int listWidgetWidth = listWidget->width();
        pixmapItem = pixmapItem.scaled(listWidgetWidth,pixmapItem.height()*listWidgetWidth/pixmapItem.width(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        item->setIcon(pixmapItem);
        listWidget->setIconSize(QSize(listWidgetWidth,pixmapItem.height()*listWidgetWidth/pixmapItem.width()));
        listWidget->addItem(item);
    }
}

void newCheck::slotOnListItemSelection(){
    int currentItemIndex = listWidget->currentRow();
    label_5->changeScreenshot(currentItemIndex);
    verticalScrollBar->setValue(currentItemIndex);
}

void newCheck::slotOnTextChanged(){
    commandManager::getInstance()->illustrate.replace(verticalScrollBar->value(),textEdit->toPlainText());
}


















