#ifndef UICENTERWIDGETHANDLER_H
#define UICENTERWIDGETHANDLER_H

#include <QWidget>
#include "CommandDef.h"

class ToolBar;
class SwitchBar;
class UiMainWindow;
class UiCenterWidgetHandler : public QObject
{
	Q_OBJECT
public:
	UiCenterWidgetHandler(QObject* parent = nullptr);
	~UiCenterWidgetHandler();

	//设置中心窗口
	void setCenterWidget(QWidget* widget);

	//设置ToolBar
	void setToolBar(Ui::ToolBarArea loc, ToolBar* toolbar);
	//设置开关栏
	void setSwitchBar(Ui::Corner loc, SwitchBar* switchBar);

	void onCenterWidgetResize();
	void onInitToolBarArea();
	void updateSwitchBar();

private slots:
	void onToolBarAreaChanged();

private:
	void calcCenterSize();
	void updateToolBar();

private:
	struct SwitchBarMap
	{
		SwitchBar* switchBar;
		Ui::Corner loc;
	};
	QList<ToolBar*> mToolBarMap;
	QList<SwitchBarMap> mSwitchBarMap;
	QWidget* mCenterWidget = nullptr;
	UiMainWindow* mParent;
	QRect pRect;
	QRect lastPRect;
};

#endif //UICENTERWIDGETHANDLER_H