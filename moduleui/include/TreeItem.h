#ifndef TREEITEM_H
#define TREEITEM_H

#include "UiGlobal.h"
#include <QVariant>
class UI_EXPORT TreeItem
{
public:
	TreeItem(TreeItem* parent = nullptr);
	TreeItem(const QString& text, TreeItem* parent = nullptr);
	~TreeItem();

	void appendChild(TreeItem* pChild);
	void insertChild(int index, TreeItem* pChild);
	void removeChild(TreeItem* p);

	QVariant data() const;
	void setData(const QVariant& value);

	int childCount() const;
	TreeItem* parent();
	TreeItem* child(int row);
	int row();

private:
	TreeItem* m_parentItem;
	QString m_text;
	QList<TreeItem*> m_childItems;
	QVariant m_data;
};

#endif	//TREEITEM_H