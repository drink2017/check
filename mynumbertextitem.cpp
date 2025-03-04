﻿#include "mynumbertextitem.h"
#include "commandmanager.h"
#include "QTextDocument"
#include "screenshotview.h"

myNumberTextItem::myNumberTextItem()
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setTextInteractionFlags(Qt::TextEditorInteraction);
    connect(document(),&QTextDocument::contentsChanged,this,&myNumberTextItem::adjustTextWidth);

    QFont font;
    font.setPointSize(screenshotView::getInstance()->getControl()->myTextWidget->settings->getNumberSize());
    this->setFont(font);
}

void myNumberTextItem::adjustTextWidth(){
    QRectF selectRect = QRectF(screenshotView::getInstance()->getSelectStart(),screenshotView::getInstance()->getSelectEnd()).normalized();
    QRectF textRect = this->mapToScene(this->boundingRect()).boundingRect();
    if(textRect.right() >= selectRect.right()){
        setTextWidth(selectRect.right() - this->scenePos().x());
    }else{
        setTextWidth(-1);
    }
}


void myNumberTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    commandManager::getInstance()->setEditingItem(true);
    QGraphicsTextItem::mousePressEvent(event);
}

void myNumberTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseMoveEvent(event);
}

void myNumberTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsTextItem::mouseReleaseEvent(event);
    commandManager::getInstance()->setEditingItem(false);
}


void myNumberTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF textRect = boundingRect();
    if(commandManager::getInstance()->numberCover){
        painter->setBrush(QBrush(Qt::white));
    }else{
        painter->setBrush(Qt::NoBrush);
    }
    painter->setPen(Qt::NoPen);
    painter->drawRect(textRect);

    QGraphicsTextItem::paint(painter,option,widget);

    screenshotView::getInstance()->getScene()->update();
}
