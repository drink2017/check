#ifndef CHECKACTION_H
#define CHECKACTION_H
#include "UiGlobal.h"
#include <QWidgetAction>

/**
 * @brief 勾选按钮
 *
 * @note 在QWidgetAction内封装QCheckBox实现勾选功能，
 *		 主要用于下拉菜单中；
 */
class UI_EXPORT CheckAction : public QWidgetAction
{
	Q_OBJECT
	UI_DECLARE_PRIVATE(CheckAction)
public:
	CheckAction(QWidget* parent = nullptr);
	CheckAction(const QString& text, QWidget* parent = nullptr);
	~CheckAction();

	//设置item名称
	void setText(const QString& text);
	//获取名称
	QString getText();

	//获取当前选中状态
	Qt::CheckState checkState() const;
	//设置当前选中状态
	void setCheckState(Qt::CheckState state);

signals:
	//勾选状态改变
	void stateChanged(int);
};

#endif CHECKACTION_H