#ifndef SWITCHBAR_H
#define SWITCHBAR_H
#include "UiGlobal.h"
#include <QWidget>
#include <QBoxLayout>

/**
 * @brief 开关栏
 *
 * @note 封装自定义开关按钮实现开关栏
 * 
 * @todo 后续可以添加按钮是横向还是纵向（目前默认纵向）（已完成）
 */
class SwitchButton;
class UI_EXPORT SwitchBar : public QWidget
{
	Q_OBJECT
	UI_DECLARE_PRIVATE(SwitchBar)
public:
	SwitchBar(QWidget* parent = nullptr);
	~SwitchBar();

	//添加开关按钮
	void addSwitchButton(SwitchButton* swBtn, const QString& name);
	//设置添加按钮是横向还是纵向
	void setDirection(QBoxLayout::Direction dir);
};

#endif	//SWITCHBAR_H