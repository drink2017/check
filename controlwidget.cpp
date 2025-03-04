﻿#include "controlwidget.h"
#include "screenshotview.h"
#include "undomanager.h"
#include "redomanager.h"
#include "myrectitem.h"
#include "myellipseitem.h"
#include "mypenitem.h"
#include "mytextitem.h"
#include "mynumberitem.h"

#include <commandmanager.h>
#include <QGuiApplication>
#include <QScreen>
#include <QApplication>
#include <QStyle>
#include <QDebug>
#include <QTimer>

controlWidget::controlWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    myColorWidget = new colorWidget();
    myColorWidget->hide();

    myTextWidget = new textWidget();
    myTextWidget->hide();

    setButtons();
    pLayout = new QHBoxLayout(this);
    pLayout->setSpacing(6);
    pLayout->setContentsMargins(6,6,6,6);

    addButtonsToLayout();
    connectToSlots();
}

void controlWidget::setLocation(QPoint selectStart,QPoint selectEnd){
    QScreen* screen = QGuiApplication::primaryScreen();
    int screenHeight = screen->size().height();
    if(!myColorWidget->isVisible() && !myTextWidget->isVisible()){
        if(selectEnd.x() < 422){
            if(selectStart.y() < 44 && (screenHeight - selectEnd.y()) < 44){
                locationRect.setRect(0,selectStart.y(),386,44);
            }else if((screenHeight - selectEnd.y()) < 44){
                locationRect.setRect(0,selectStart.y() - 44,386,44);
            }else{
                locationRect.setRect(0,selectEnd.y(),386,44);
            }
        }else{
            if(selectStart.y() < 44 && (screenHeight - selectEnd.y()) < 44){
                locationRect.setRect(selectEnd.x() - 422,selectStart.y(),386,44);
            }else if((screenHeight - selectEnd.y()) < 44){
                locationRect.setRect(selectEnd.x() - 422,selectStart.y() - 44,386,44);
            }else{
                locationRect.setRect(selectEnd.x() - 422,selectEnd.y(),386,44);
            }
        }
    }else if(myColorWidget->isVisible() && !myTextWidget->isVisible()){
        if(selectEnd.x() < 422){
            if(selectStart.y() < 98 && (screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(0,selectStart.y(),386,44);
                myColorWidget->setLocationBelow();
            }else if((screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(0,selectStart.y() - 44,386,44);
                myColorWidget->setLocationAbove();
            }else{
                locationRect.setRect(0,selectEnd.y(),386,44);
                myColorWidget->setLocationBelow();
            }
        }else{
            if(selectStart.y() < 98 && (screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(selectEnd.x() - 422,selectStart.y(),386,44);
                myColorWidget->setLocationBelow();
            }else if((screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(selectEnd.x() - 422,selectStart.y() - 44,386,44);
                myColorWidget->setLocationAbove();
            }else{
                locationRect.setRect(selectEnd.x() - 422,selectEnd.y(),386,44);
                myColorWidget->setLocationBelow();
            }
        }
    }else if(!myColorWidget->isVisible() && myTextWidget->isVisible()){
        if(selectEnd.x() < 422){
            if(selectStart.y() < 98 && (screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(0,selectStart.y(),386,44);
                myTextWidget->setLocationBelow();
            }else if((screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(0,selectStart.y() - 44,386,44);
                myTextWidget->setLocationAbove();
            }else{
                locationRect.setRect(0,selectEnd.y(),386,44);
                myTextWidget->setLocationBelow();
            }
        }else{
            if(selectStart.y() < 98 && (screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(selectEnd.x() - 422,selectStart.y(),386,44);
                myTextWidget->setLocationBelow();
            }else if((screenHeight - selectEnd.y()) < 98){
                locationRect.setRect(selectEnd.x() - 422,selectStart.y() - 44,386,44);
                myTextWidget->setLocationAbove();
            }else{
                locationRect.setRect(selectEnd.x() - 422,selectEnd.y(),386,44);
                myTextWidget->setLocationBelow();
            }
        }
    }
    setGeometry(locationRect);
}

void controlWidget::setButtons(){
    //添加10个按钮
    pRectButton = new QPushButton(this);
    pRectButton->setFixedSize(QSize(32,32));
    pRectButton->setToolTip(u8"矩形");
    pRectButton->setCheckable(true);
    pRectButton->setChecked(false);
    QIcon rectIcon(":/icons/controlWidget/rectangle.png");
    pRectButton->setIcon(rectIcon);

    pRoundButton = new QPushButton(this);
    pRoundButton->setToolTip(u8"圆");
    pRoundButton->setFixedSize(QSize(32,32));
    pRoundButton->setCheckable(true);
    pRoundButton->setChecked(false);
    QIcon roundIcon(":/icons/controlWidget/ellipse.png");
    pRoundButton->setIcon(roundIcon);

    pArrowButton = new QPushButton(this);
    pArrowButton->setFixedSize(QSize(32,32));
    pArrowButton->setToolTip("箭头");
    pArrowButton->setCheckable(true);
    pArrowButton->setChecked(false);
    QIcon arrowIcon(":/icons/controlWidget/arrow.png");
    pArrowButton->setIcon(arrowIcon);

    pPenButton = new QPushButton(this);
    pPenButton->setFixedSize(QSize(32,32));
    pPenButton->setToolTip(u8"画笔");
    pPenButton->setCheckable(true);
    pPenButton->setChecked(false);
    QIcon penIcon(":/icons/controlWidget/pen.png");
    pPenButton->setIcon(penIcon);

    pTextButton = new QPushButton;
    pTextButton->setFixedSize(QSize(32,32));
    pTextButton->setToolTip(u8"文字");
    pTextButton->setCheckable(true);
    pTextButton->setChecked(false);
    QIcon textIcon(":/icons/controlWidget/text.png");
    pTextButton->setIcon(textIcon);

    pSerialButton = new QPushButton;
    pSerialButton->setFixedSize(QSize(32,32));
    pSerialButton->setToolTip("序号笔");
    pSerialButton->setCheckable(true);
    pSerialButton->setChecked(false);
    QIcon serialIcon(":/icons/controlWidget/serial.png");
    pSerialButton->setIcon(serialIcon);

    pUndoButton = new QPushButton;
    pUndoButton->setFixedSize(QSize(32,32));
    pUndoButton->setToolTip(u8"撤销");
    QIcon undoIcon(":/icons/controlWidget/undo.png");
    pUndoButton->setIcon(undoIcon);

    pRedoButton = new QPushButton;
    pRedoButton->setToolTip(u8"重做");
    pRedoButton->setFixedSize(QSize(32,32));
    QIcon redoIcon(":/icons/controlWidget/redo.png");
    pRedoButton->setIcon(redoIcon);

    pNOButton = new QPushButton;
    pNOButton->setFixedSize(QSize(32,32));
    pNOButton->setToolTip(u8"退出截图");
    QIcon noIcon = QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton);
    pNOButton->setIcon(noIcon);

    pOKButton = new QPushButton;
    pOKButton->setFixedSize(QSize(32,32));
    QIcon okIcon(":/icons/controlWidget/ok.png");
    pOKButton->setIcon(okIcon);
    pOKButton->setToolTip("确认截图");
}

void controlWidget::addButtonsToLayout(){
    pLayout->addWidget(pRectButton);
    pLayout->addWidget(pRoundButton);
    pLayout->addWidget(pArrowButton);
    pLayout->addWidget(pPenButton);
    pLayout->addWidget(pTextButton);
    pLayout->addWidget(pSerialButton);
    pLayout->addWidget(pUndoButton);
    pLayout->addWidget(pRedoButton);
    pLayout->addWidget(pNOButton);
    pLayout->addWidget(pOKButton);
}

void controlWidget::connectToSlots(){
    connect(pRectButton,&QPushButton::clicked,this,&controlWidget::rectButtonStatu);
    connect(pRoundButton,&QPushButton::clicked,this,&controlWidget::roundButtonStatu);
    connect(pArrowButton,&QPushButton::clicked,this,&controlWidget::arrowButtonStatu);
    connect(pPenButton,&QPushButton::clicked,this,&controlWidget::penButtonStatu);
    connect(pTextButton,&QPushButton::clicked,this,&controlWidget::textButtonStatu);
    connect(pSerialButton,&QPushButton::clicked,this,&controlWidget::numberButtonStatu);
    connect(pUndoButton,&QPushButton::clicked,this,&controlWidget::undo);
    connect(pRedoButton,&QPushButton::clicked,this,&controlWidget::redo);
    connect(pNOButton,&QPushButton::clicked,this,&controlWidget::quit);
    connect(pOKButton,&QPushButton::clicked,this,&controlWidget::shot);
}

void controlWidget::rectButtonStatu(){
    pRoundButton->setChecked(false);
    pArrowButton->setChecked(false);
    pPenButton->setChecked(false);
    pTextButton->setChecked(false);
    pSerialButton->setChecked(false);
    if(pRectButton->isChecked()){
        emit enableDrawRect();
        emit disableDrawRound();
        emit disableDrawArrow();
        emit disableDrawPen();
        emit disableDrawText();
        emit disableDrawNumber();
        commandManager::getInstance()->dragTotally = false;
        myTextWidget->hide();
        myColorWidget->setType(widgetType::rect);
        myColorWidget->show();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }else{
        myColorWidget->hide();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }
}

void controlWidget::roundButtonStatu(){
    pRectButton->setChecked(false);
    pArrowButton->setChecked(false);
    pPenButton->setChecked(false);
    pTextButton->setChecked(false);
    pSerialButton->setChecked(false);
    if(pRoundButton->isChecked()){
        emit enableDrawRound();
        emit disableDrawRect();
        emit disableDrawArrow();
        emit disableDrawPen();
        emit disableDrawText();
        emit disableDrawNumber();
        commandManager::getInstance()->dragTotally = false;
        myTextWidget->hide();
        myColorWidget->setType(widgetType::ellipse);
        myColorWidget->show();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }else{
        myColorWidget->hide();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }
}

void controlWidget::arrowButtonStatu(){
    pRectButton->setChecked(false);
    pRoundButton->setChecked(false);
    pPenButton->setChecked(false);
    pTextButton->setChecked(false);
    pSerialButton->setChecked(false);
    if(pArrowButton->isChecked()){
        emit enableDrawArrow();
        emit disableDrawRect();
        emit disableDrawRound();
        emit disableDrawPen();
        emit disableDrawText();
        emit disableDrawNumber();
        commandManager::getInstance()->dragTotally = false;
        myTextWidget->hide();
        myColorWidget->setType(widgetType::arrow);
        myColorWidget->show();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }else{
        myColorWidget->hide();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }
}

void controlWidget::penButtonStatu(){
    pRectButton->setChecked(false);
    pRoundButton->setChecked(false);
    pArrowButton->setChecked(false);
    pTextButton->setChecked(false);
    pSerialButton->setChecked(false);
    if(pPenButton->isChecked()){
        emit enableDrawPen();
        emit disableDrawRect();
        emit disableDrawRound();
        emit disableDrawArrow();
        emit disableDrawText();
        emit disableDrawNumber();
        commandManager::getInstance()->dragTotally = false;
        myTextWidget->hide();
        myColorWidget->setType(widgetType::pen);
        myColorWidget->show();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }else{
        myColorWidget->hide();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }
}

void controlWidget::textButtonStatu(){
    pRectButton->setChecked(false);
    pRoundButton->setChecked(false);
    pArrowButton->setChecked(false);
    pPenButton->setChecked(false);
    pSerialButton->setChecked(false);
    if(pTextButton->isChecked()){
        emit disableDrawRect();
        emit disableDrawRound();
        emit disableDrawArrow();
        emit disableDrawPen();
        emit enableDrawText();
        emit disableDrawNumber();
        commandManager::getInstance()->dragTotally = false;
        myColorWidget->hide();
        myTextWidget->setType(textWidgetType::text);
        myTextWidget->show();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }else{
        myTextWidget->hide();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }
}

void controlWidget::numberButtonStatu(){
    pRectButton->setChecked(false);
    pRoundButton->setChecked(false);
    pArrowButton->setChecked(false);
    pPenButton->setChecked(false);
    pTextButton->setChecked(false);
    if(pSerialButton->isChecked()){
        emit disableDrawRect();
        emit disableDrawRound();
        emit disableDrawArrow();
        emit disableDrawPen();
        emit disableDrawText();
        emit enableDrawNumber();
        commandManager::getInstance()->dragTotally = false;
        myColorWidget->hide();
        myTextWidget->setType(textWidgetType::serial);
        myTextWidget->show();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }else{
        myTextWidget->hide();
        QPoint selectStart = screenshotView::getInstance()->getSelectStart();
        QPoint selectEnd = screenshotView::getInstance()->getSelectEnd();
        setLocation(QRect(selectStart,selectEnd).topLeft(),QRect(selectStart,selectEnd).bottomRight());
    }
}

void controlWidget::undo(){
    undoManager* myUndoManager = undoManager::getInstance();
    redoManager* myRedoManager = redoManager::getInstance();
    if(myUndoManager->isEmpty()){
        return;
    }else{
        order* undoOrder = myUndoManager->popOrder();
        QQueue<QGraphicsItem*> addItem = undoOrder->getAddItem();
        QQueue<QGraphicsItem*> deleteItem = undoOrder->getDeleteItem();
        if(!addItem.isEmpty() && deleteItem.isEmpty()){
            QGraphicsItem* item = addItem.back();
            screenshotView::getInstance()->getScene()->removeItem(item);
            undoOrder->clearAddItem();
            undoOrder->addToDeleteItem(item);
            myRedoManager->pushOrder(undoOrder);
            if(typeid (*item) == typeid (myNumberItem)){
                commandManager::getInstance()->number--;
            }
        }else if(!addItem.isEmpty() && !deleteItem.isEmpty()){
            auto& itemHasDeleted = *(deleteItem.back());
            if(typeid (itemHasDeleted) == typeid (myRectItem)){
                myRectItem* beforeMoveItem = dynamic_cast<myRectItem*>(deleteItem.back());
                myRectItem* afterMoveItem = dynamic_cast<myRectItem*>(addItem.back());
                QRectF afterMoveRect = afterMoveItem->rect();
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setRect(beforeMoveItem->rect());
                afterMoveItem->setPos(beforeMoveItem->pos());
                afterMoveItem->updateEllipseHandles();
                beforeMoveItem->setRect(afterMoveRect);
                beforeMoveItem->setPos(afterMovePos);
                undoOrder->clearAddItem();
                undoOrder->clearDeleteItem();
                undoOrder->addToAddItem(afterMoveItem);
                undoOrder->addToDeleteItem(beforeMoveItem);
                myRedoManager->pushOrder(undoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myEllipseItem)){
                myEllipseItem* beforeMoveItem = dynamic_cast<myEllipseItem*>(deleteItem.back());
                myEllipseItem* afterMoveItem = dynamic_cast<myEllipseItem*>(addItem.back());
                QRectF afterMoveRect = afterMoveItem->rect();
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setRect(beforeMoveItem->rect());
                afterMoveItem->setPos(beforeMoveItem->pos());
                afterMoveItem->updateEllipseHandles();
                beforeMoveItem->setRect(afterMoveRect);
                beforeMoveItem->setPos(afterMovePos);
                undoOrder->clearAddItem();
                undoOrder->clearDeleteItem();
                undoOrder->addToAddItem(afterMoveItem);
                undoOrder->addToDeleteItem(beforeMoveItem);
                myRedoManager->pushOrder(undoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myArrowItem)){
                myArrowItem* beforeMoveItem = dynamic_cast<myArrowItem*>(deleteItem.back());
                myArrowItem* afterMoveItem = dynamic_cast<myArrowItem*>(addItem.back());
                QPointF afterMoveStart = afterMoveItem->getStart();
                QPointF afterMoveEnd = afterMoveItem->getEnd();
                afterMoveItem->setStart((afterMoveItem->mapFromScene((beforeMoveItem->mapToScene(beforeMoveItem->getStart())))).toPoint());
                afterMoveItem->setEnd((afterMoveItem->mapFromScene(beforeMoveItem->mapToScene(beforeMoveItem->getEnd()))).toPoint());
                afterMoveItem->updateEllipseHandles();
                beforeMoveItem->setStart((beforeMoveItem->mapFromScene(afterMoveItem->mapToScene(afterMoveStart))).toPoint());
                beforeMoveItem->setEnd((beforeMoveItem->mapFromScene(afterMoveItem->mapToScene(afterMoveEnd))).toPoint());
                undoOrder->clearAddItem();
                undoOrder->clearDeleteItem();
                undoOrder->addToAddItem(afterMoveItem);
                undoOrder->addToDeleteItem(beforeMoveItem);
                myRedoManager->pushOrder(undoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myPenItem)){
                myPenItem* beforeMoveItem = dynamic_cast<myPenItem*>(deleteItem.back());
                myPenItem* afterMoveItem = dynamic_cast<myPenItem*>(addItem.back());
                QPainterPath afterMovePath = afterMoveItem->path();
                afterMoveItem->setPath(afterMoveItem->mapFromScene(beforeMoveItem->mapToScene(beforeMoveItem->path())));
                beforeMoveItem->setPath(beforeMoveItem->mapFromScene(afterMoveItem->mapToScene(afterMovePath)));
                undoOrder->clearAddItem();
                undoOrder->clearDeleteItem();
                undoOrder->addToAddItem(afterMoveItem);
                undoOrder->addToDeleteItem(beforeMoveItem);
                myRedoManager->pushOrder(undoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myTextItem)){
                myTextItem* beforeMoveItem = dynamic_cast<myTextItem*>(deleteItem.back());
                myTextItem* afterMoveItem = dynamic_cast<myTextItem*>(addItem.back());
                if(!afterMoveItem->scene()){
                    screenshotView::getInstance()->getScene()->addItem(afterMoveItem);
                }
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setPos(beforeMoveItem->pos());
                beforeMoveItem->setPos(afterMovePos);
                undoOrder->clearAddItem();
                undoOrder->clearDeleteItem();
                undoOrder->addToAddItem(afterMoveItem);
                undoOrder->addToDeleteItem(beforeMoveItem);
                myRedoManager->pushOrder(undoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myNumberItem)){
                myNumberItem* beforeMoveItem = dynamic_cast<myNumberItem*>(deleteItem.back());
                myNumberItem* afterMoveItem = dynamic_cast<myNumberItem*>(addItem.back());
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setPos(beforeMoveItem->pos());
                beforeMoveItem->setPos(afterMovePos);
                undoOrder->clearAddItem();
                undoOrder->clearDeleteItem();
                undoOrder->addToAddItem(afterMoveItem);
                undoOrder->addToDeleteItem(beforeMoveItem);
                myRedoManager->pushOrder(undoOrder);
            }
        }
    }
}

void controlWidget::redo(){
    undoManager* myUndoManager = undoManager::getInstance();
    redoManager* myRedoManager = redoManager::getInstance();
    if(myRedoManager->isEmpty()){
        return;
    }else{
        order* redoOrder = myRedoManager->popOrder();
        QQueue<QGraphicsItem*> addItem = redoOrder->getAddItem();
        QQueue<QGraphicsItem*> deleteItem = redoOrder->getDeleteItem();
        if(addItem.isEmpty() && !deleteItem.isEmpty()){
            QGraphicsItem* item = deleteItem.back();
            screenshotView::getInstance()->getScene()->addItem(item);
            redoOrder->clearDeleteItem();
            redoOrder->addToAddItem(item);
            myUndoManager->pushOrder(redoOrder);
            if(typeid(*item) == typeid (myNumberItem)){
                commandManager::getInstance()->number++;
            }
        }else if(!addItem.isEmpty() && !deleteItem.isEmpty()){
            auto& itemHasDeleted = *(deleteItem.back());
            if(typeid (itemHasDeleted) == typeid (myRectItem)){
                myRectItem* beforeMoveItem = dynamic_cast<myRectItem*>(deleteItem.back());
                myRectItem* afterMoveItem = dynamic_cast<myRectItem*>(addItem.back());
                QRectF afterMoveRect = afterMoveItem->rect();
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setRect(beforeMoveItem->rect());
                afterMoveItem->setPos(beforeMoveItem->pos());
                afterMoveItem->updateEllipseHandles();
                beforeMoveItem->setRect(afterMoveRect);
                beforeMoveItem->setPos(afterMovePos);
                redoOrder->clearAddItem();
                redoOrder->clearDeleteItem();
                redoOrder->addToAddItem(afterMoveItem);
                redoOrder->addToDeleteItem(beforeMoveItem);
                myUndoManager->pushOrder(redoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myEllipseItem)){
                myEllipseItem* beforeMoveItem = dynamic_cast<myEllipseItem*>(deleteItem.back());
                myEllipseItem* afterMoveItem = dynamic_cast<myEllipseItem*>(addItem.back());
                QRectF afterMoveRect = afterMoveItem->rect();
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setRect(beforeMoveItem->rect());
                afterMoveItem->setPos(beforeMoveItem->pos());
                afterMoveItem->updateEllipseHandles();
                beforeMoveItem->setRect(afterMoveRect);
                beforeMoveItem->setPos(afterMovePos);
                redoOrder->clearAddItem();
                redoOrder->clearDeleteItem();
                redoOrder->addToAddItem(afterMoveItem);
                redoOrder->addToDeleteItem(beforeMoveItem);
                myUndoManager->pushOrder(redoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myArrowItem)){
                myArrowItem* beforeMoveItem = dynamic_cast<myArrowItem*>(deleteItem.back());
                myArrowItem* afterMoveItem = dynamic_cast<myArrowItem*>(addItem.back());
                QPointF afterMoveStart = afterMoveItem->getStart();
                QPointF afterMoveEnd = afterMoveItem->getEnd();
                afterMoveItem->setStart((afterMoveItem->mapFromScene((beforeMoveItem->mapToScene(beforeMoveItem->getStart())))).toPoint());
                afterMoveItem->setEnd((afterMoveItem->mapFromScene(beforeMoveItem->mapToScene(beforeMoveItem->getEnd()))).toPoint());
                afterMoveItem->updateEllipseHandles();
                beforeMoveItem->setStart((beforeMoveItem->mapFromScene(afterMoveItem->mapToScene(afterMoveStart))).toPoint());
                beforeMoveItem->setEnd((beforeMoveItem->mapFromScene(afterMoveItem->mapToScene(afterMoveEnd))).toPoint());
                redoOrder->clearAddItem();
                redoOrder->clearDeleteItem();
                redoOrder->addToAddItem(afterMoveItem);
                redoOrder->addToDeleteItem(beforeMoveItem);
                myUndoManager->pushOrder(redoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myPenItem)){
                myPenItem* beforeMoveItem = dynamic_cast<myPenItem*>(deleteItem.back());
                myPenItem* afterMoveItem = dynamic_cast<myPenItem*>(addItem.back());
                QPainterPath afterMovePath = afterMoveItem->path();
                afterMoveItem->setPath(afterMoveItem->mapFromScene(beforeMoveItem->mapToScene(beforeMoveItem->path())));
                beforeMoveItem->setPath(beforeMoveItem->mapFromScene(afterMoveItem->mapToScene(afterMovePath)));
                redoOrder->clearAddItem();
                redoOrder->clearDeleteItem();
                redoOrder->addToAddItem(afterMoveItem);
                redoOrder->addToDeleteItem(beforeMoveItem);
                myUndoManager->pushOrder(redoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myTextItem)){
                myTextItem* beforeMoveItem = dynamic_cast<myTextItem*>(deleteItem.back());
                myTextItem* afterMoveItem = dynamic_cast<myTextItem*>(addItem.back());
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setPos(beforeMoveItem->pos());
                beforeMoveItem->setPos(afterMovePos);
                redoOrder->clearAddItem();
                redoOrder->clearDeleteItem();
                redoOrder->addToAddItem(afterMoveItem);
                redoOrder->addToDeleteItem(beforeMoveItem);
                myUndoManager->pushOrder(redoOrder);
            }else if(typeid (itemHasDeleted) == typeid (myNumberItem)){
                myNumberItem* beforeMoveItem = dynamic_cast<myNumberItem*>(deleteItem.back());
                myNumberItem* afterMoveItem = dynamic_cast<myNumberItem*>(addItem.back());
                QPointF afterMovePos = afterMoveItem->pos();
                afterMoveItem->setPos(beforeMoveItem->pos());
                beforeMoveItem->setPos(afterMovePos);
                redoOrder->clearAddItem();
                redoOrder->clearDeleteItem();
                redoOrder->addToAddItem(afterMoveItem);
                redoOrder->addToDeleteItem(beforeMoveItem);
                myUndoManager->pushOrder(redoOrder);
            }
        }
    }
}

void controlWidget::shot(){
    screenshotView::getInstance()->hideSelectRectHandles();
    screenshotView::getInstance()->getInfo()->hide();
    screenshotView::getInstance()->getControl()->hide();
    screenshotView::getInstance()->getControl()->myTextWidget->hide();
    screenshotView::getInstance()->getControl()->myColorWidget->hide();
    screenshotView::getInstance()->getCurrentSelectItem()->hide();

    //等待rectHandles被隐藏了再截屏
    QEventLoop loop;
    QTimer::singleShot(0.0000000000000000000000000000000000000000000000000000000000000000000000000001, &loop, &QEventLoop::quit); //？？？？不加不行
    loop.exec();

    QScreen *screen = QGuiApplication::primaryScreen();
    QRectF captureRect = QRectF(screenshotView::getInstance()->getSelectStart(),screenshotView::getInstance()->getSelectEnd());
    QPixmap screenshot = screen->grabWindow(0,captureRect.x(),captureRect.y(),captureRect.width(),captureRect.height());
    if(screenshotView::getInstance()->getType() == shotType::newShot){
        commandManager::getInstance()->screenshots.append(screenshot);
        commandManager::getInstance()->illustrate.append("校核说明：\n");
    }else if(screenshotView::getInstance()->getType() == shotType::replace){
        commandManager::getInstance()->screenshots.replace(commandManager::getInstance()->screenshotValue,screenshot);
        commandManager::getInstance()->illustrate.replace(commandManager::getInstance()->screenshotValue,"校核说明：\n");
    }
    screenshotView::getInstance()->getCheck()->updateListWidget();
    screenshotView::getInstance()->getCheck()->updateScreenshots();
    commandManager::getInstance()->quit();
}

QRect controlWidget::getLocationRect(){
    return locationRect;
}

void controlWidget::updateButtonStatu(){
    if(commandManager::getInstance()->isDrawingRect()){
        pRectButton->setChecked(true);
    }else{
        pRectButton->setChecked(false);
    }
    if(commandManager::getInstance()->isDrawingEllipse()){
        pRoundButton->setChecked(true);
    }else{
        pRoundButton->setChecked(false);
    }
    if(commandManager::getInstance()->isDrawingArrow()){
        pArrowButton->setChecked(true);
    }else{
        pArrowButton->setChecked(false);
    }
    if(commandManager::getInstance()->isDrawingPen()){
        pPenButton->setChecked(true);
    }else{
        pPenButton->setChecked(false);
    }
    if(commandManager::getInstance()->isDrawingText()){
        pTextButton->setChecked(true);
    }else{
        pTextButton->setChecked(false);
    }
    if(commandManager::getInstance()->isDrawingNumber()){
        pSerialButton->setChecked(true);
    }else{
        pSerialButton->setChecked(false);
    }
}

























