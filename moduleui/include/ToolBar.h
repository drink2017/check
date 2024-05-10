#ifndef TOOLBAR_H
#define TOOLBAR_H
#include "UiGlobal.h"
#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QEvent>
#include <QBoxLayout>
#include "CommandDef.h"
/**
 * @brief 工具栏
 *
 * @note 封装可移动但不可停靠，能够纵向和横向的工具条,
 *		 新增工具栏只能在父类窗口内移动；
 * 
 * @todo 有bug，会导致报QCoreApplication::exec: The event loop is already running;（似乎已解决，后续没出现过，不清楚原因）；
 *		 后续添加按钮大小和按钮图标大小接口
 *		 1、鼠标点击工具栏时会识别的父窗口的焦点；
 *		 2、鼠标点击工具拖动区域按下时，工具栏左上角会移动到鼠标位置；
 *		 3、碰撞检测；
 *		 4、竖着的toolbar内的按钮有偏移
 */
class UI_EXPORT ToolBar : public QWidget
{
	Q_OBJECT
	UI_DECLARE_PRIVATE(ToolBar)
public:
	ToolBar(QWidget* parent = nullptr);
	~ToolBar();

	//覆盖sizeHint
	virtual QSize sizeHint() const Q_DECL_OVERRIDE;

	//设置是否可以移动
	void setMovable(bool);
	bool getMovable();
	//设置方向
	void setOrientation(Qt::Orientation orientation);
	//获取方向
	Qt::Orientation Orientation();
	//添加按钮
	void addToolButton(const QIcon& icon, const QString& text);
	void addToolButton(QToolButton* toolButton);
	//设置图标比例
	void setIconScale(const qreal iconscale);
	//设置工具栏位置
	void setToolBarArea(Ui::ToolBarArea loc);
	//获取工具栏位置
	Ui::ToolBarArea getToolBarArea();

protected:
	//监听拖动控件，判断是否可以移动，以及实现移动，监听父窗口是否改变
	virtual bool eventFilter(QObject* watched, QEvent* e) Q_DECL_OVERRIDE;

signals:
	void signalToolBarAreaChanged();
};

/**
 * @brief 拖动button
 */
class DragButton : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString orientation READ getOrientation WRITE setOrientation)	//自定义属性状态
public:
	DragButton(QWidget* p = nullptr);
	//获取方向
	QString getOrientation();
	//设置方向
	void setOrientation(QString ori);

private:
	QString orientation;
};

#endif	//TOOLBAR_H

