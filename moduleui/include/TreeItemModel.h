#ifndef TREEITEMMODEL_H
#define TREEITEMMODEL_H

#include "UiGlobal.h"
#include <QAbstractItemModel>

class TreeItem;
class UI_EXPORT TreeItemModel : public QAbstractItemModel
{
public:
    TreeItemModel(QObject* parent = nullptr);
    ~TreeItemModel();

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex& index) const;

    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;

    bool hasChildren(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::UserRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::UserRole);

    TreeItem* rootItem() { return m_rootItem; }

    void updateTree();

private:
    TreeItem* itemFromIndex(const QModelIndex& index) const;

private:
    TreeItem* m_rootItem;
};

#endif	//TREEITEMMODEL_H