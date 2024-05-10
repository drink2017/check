#ifndef TREEVIEW_H
#define TREEVIEW_H
#include "UiGlobal.h"
#include <QTreeView>

class TreeItemDelegate;
class UI_EXPORT TreeView : public QTreeView
{
	Q_OBJECT
public:
	enum TreeViewType	//是否有状态图标
	{
		Default,		//没有图标的
		StatusIcon	//有状态图标的
	};

	explicit TreeView(TreeViewType type, QWidget* parent = nullptr);
	~TreeView();

private:
	TreeItemDelegate* m_delegate;	//节点委托类（负责生成显隐按钮和状态图标）
};

#endif	//TREEVIEW_H