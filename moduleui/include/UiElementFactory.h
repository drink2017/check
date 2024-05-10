#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H
#include "UiGlobal.h"
#include "CommandDef.h"
#include <QScopedPointer>
#include "UiStyleOption.h"
/**
 * @brief Ui的子元素创建的工厂
 *
 * @note 内部创建子元素都通过UiElementFactory来创建
 */
class QWidget;
class FramelessHelper;
class MainButton;
class WindowButtonGroup;
class TitleBar;
class DockWidgetTitle;
class UiDockAreaTabBar;
class DockWidgetTab;
class DockWidget;
class ScaleComBoBox;
class UI_EXPORT UiElementFactory
{
public:
    UiElementFactory();
    virtual ~UiElementFactory();
    //创建无边框窗体
    virtual FramelessHelper* createFramelessHelper(QWidget* parent);
    //创建标题栏主按钮
    virtual MainButton* createMainButton(QWidget* parent);
    //创建放大缩小还原按钮组
    virtual WindowButtonGroup* createWindowButtonGroup(QWidget* parent);
    //创建标题栏
    virtual TitleBar* createTitleBar(QWidget* parent);
    //创建dock标题栏
    virtual DockWidgetTitle* createDockWidgetTitle(DockWidget* parent);
    //创建比例尺
    virtual ScaleComBoBox* createScaleComBoBox(QWidget* parent);

    // SARibbonStyleOption可以进行继承，此函数无需设置为虚函数
    UiStyleOption& getUiStyleOption();
    void setUiStyleOption(UiStyleOption* opt);

private:
    QScopedPointer< UiStyleOption > mStyleOption;
};
#endif  // UIELEMENTCREATEDELEGATE_H
