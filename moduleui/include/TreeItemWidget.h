#ifndef TREEITEMWIDGET_H
#define TREEITEMWIDGET_H
#include "UiGlobal.h"
#include "CommandDef.h"
#include <QWidget>
class UI_EXPORT TreeItemWidget : public QWidget
{
	Q_OBJECT
	UI_DECLARE_PRIVATE(TreeItemWidget)
public:
	TreeItemWidget(QWidget* parent = nullptr);
	~TreeItemWidget();
};

#endif	//TREEITEMWIDGET_H