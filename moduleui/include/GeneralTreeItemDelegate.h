﻿#ifndef GENERALTREEITEMDELEGATE_H
#define GENERALTREEITEMDELEGATE_H

#include "UiGlobal.h"
#include <QStyledItemDelegate>
#include <QPushButton>

class UI_EXPORT GeneralTreeItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    GeneralTreeItemDelegate(QObject* parent = 0);
    ~GeneralTreeItemDelegate();
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

signals:
    void open(const QModelIndex& index);
    void deleteData(const QModelIndex& index);

private:
    QPoint m_mousePoint;  // 鼠标位置
    QScopedPointer<QPushButton> m_pOpenButton;
    //QScopedPointer<QPushButton> m_pDeleteButton;
    QStringList m_list;
    int m_nSpacing;  // 按钮之间的间距
    int m_nWidth;  // 按钮宽度
    int m_nHeight;  // 按钮高度
    int m_nType;  // 按钮状态-1：划过 2：按下
};

#endif //GENERALTREEITEMDELEGATE_H