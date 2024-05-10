#ifndef TREEITEMDELEGATE_H
#define TREEITEMDELEGATE_H

#include "UiGlobal.h"
#include <QStyledItemDelegate>

class UI_EXPORT TreeItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TreeItemDelegate(bool hideStatus, QObject* parent = 0);
    ~TreeItemDelegate();
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setNodeStatus(bool status);

signals:
    void signalHideStatus(bool status);
    void signalNodeStatus(bool status);

private:
    int m_nSpacing;  // 按钮之间的间距
    int m_nRadius;  //状态标志半径
    bool m_nodeStatus;      //节点状态
};

#endif //TREEITEMDELEGATE_H