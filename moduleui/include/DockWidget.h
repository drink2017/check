#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H
#include "UiGlobal.h"
#include <QDockWidget>
#include <QToolBar>
/**
 * @brief dock窗体
 *
 * @note 封装QDockWidget，实现自定义dock标题栏，以及添加菜单栏
 * 
 * @todo 后续可能dock部分需要重写
 */
class UI_EXPORT DockWidget : public QDockWidget
{
	Q_OBJECT
	UI_DECLARE_PRIVATE(DockWidget)
public:
	DockWidget(const QString& title, QWidget* parent = nullptr);
	~DockWidget();

	//覆写setWidget
	void setWidget(QWidget* widget);
	//添加工具栏
	void setDockToolBar(QWidget* widget);


protected:
	void insertWidget(int index, QWidget* widget);
//	void dragEnterEvent(QDragEnterEvent* event) override;
//	void dragMoveEvent(QDragMoveEvent* event) override;
//	Qt::DockWidgetArea adjustCurArea(const QPoint& pos) const;
};

#endif //DOCKWIDGET_H