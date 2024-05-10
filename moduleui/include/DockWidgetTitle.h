#ifndef DOCKWIDGETTITLE_H
#define DOCKWIDGETTITLE_H
#include "UiGlobal.h"
#include <QFrame>
#include <QWidget>
#include <QToolButton>
#include <QToolBar>
/**
 * @brief dock标题栏
 *
 * @note 自定义dock标题栏，显示dock名称，以及关闭按钮；
 *		 新增工具栏，把工具栏和标题栏放在一个widget中，
		 以便能添加到dock中；
 * 
 * @todo 后续实现autohide按钮功能
 * 要实现 QDockWidget 的自动隐藏功能，可以使用 setAllowedAreas() 方法来限制它可以停靠的区域，并使用 setFeatures() 方法来设置它的停靠行为。以下是一个示例代码：
 * QDockWidget *dockWidget = new QDockWidget("Dock Widget", this);
 * dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
 * dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
 * dockWidget->setFloating(true);
 * 上述代码创建了一个名为 “Dock Widget” 的 QDockWidget 对象，并将它限制在左侧和右侧停靠区域中。它具有可移动、可浮动和可关闭的功能，并且默认情况下是浮动状态。
 * 为了实现自动隐藏功能，可以使用 setAutoFillBackground() 方法来设置是否自动填充背景。当设置为 true 时，如果 QDockWidget 处于浮动状态并且不处于活动状态，它将自动隐藏。以下是一个示例代码：
 * QDockWidget *dockWidget = new QDockWidget("Dock Widget", this);
 * dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
 * dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
 * dockWidget->setFloating(true);
 * dockWidget->setAutoFillBackground(true);
 * 这样，当 QDockWidget 处于浮动状态但不是活动状态时，它将自动隐藏。
 */
class DockWidget;
class DockWidgetTitle : public QFrame
{
	Q_OBJECT
	UI_DECLARE_PRIVATE(DockWidgetTitle)
public:
	DockWidgetTitle(DockWidget* parent);
	~DockWidgetTitle();

	void setDockToolBar(QToolBar* bar);

	//覆盖minimumSizeHint，设置窗体最小尺寸
	virtual QSize minimumSizeHint() const override;
	//覆盖sizeHint，设置窗体尺寸
	QSize sizeHint() const;

protected:
	// 监听父窗口是否发生变化
	virtual bool eventFilter(QObject* obj, QEvent* event);

protected slots:
	Q_SLOT void onAutoHideButtonClicked();
	Q_SLOT void onCloseButtonClicked();
};

/**
 * @brief 对QToolButton进行封装
 */
class DockWidgetToolButton : public QToolButton
{
	Q_OBJECT
public:
	DockWidgetToolButton(QWidget* p = nullptr);
};

#endif //DOCKWIDGETTITLE_H