#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H
#include "UiGlobal.h"
#include "CommandDef.h"
#include <QWidget>
#include <QMainWindow>

/**
 * @brief 封装QMainWindow，实现自定义窗口
 *
 * @note 包含标题栏，侧边栏，dock窗口，状态栏，可任意拖放的工具条
 * 
 * @todo 1、后续需要研究控件之间的碰撞检测，在拖动控件时检测是否触碰到其他控件，
         来判断是否能够继续拖动；
         2、需要添加右键菜单的样式设计;
         3、主菜单栏的子项可能需要和勾选按钮一样封装，实现图标颜色的悬浮改变；
         4、全屏时拖动标题栏，会缩小，当鼠标又移到window顶部时会自动全屏，同vs；
         5、封装一些qt的控件，如qradiobutton，lineedit、checkbox、combobox;(优先)
         6、菜单栏可以添加动画；
 * @question 1、无边框下方和右方因为中心窗口覆盖无法拖动；(添加底部状态栏和右侧边距4px，已解决)
 *           2、工具栏长度超出父窗口时，无法拖动，应该是拖动的判定算法问题；
 *              （解决方法：修改算法或增加一个超出范围时折叠工具栏）
 *           3、Dialog标题栏和中心窗口边不对称（和阴影设置相关）；（3d那边treeview没
                设置样式造成的，已解决）
 *           4、工具栏3d部分显示有问题，圆角没有被隐藏，而且背景会有重影；(已解决，3d底层替换为QOopenGLWidget)
 *           5、状态栏高度有点矮，需要提供设置高度和宽度的接口；(已解决)
 *           6、打开dock的时候整个中心窗体会向右移导致工具栏等依赖中心窗体的
 *              控件位置改变（解决方法：在点击sidebar按钮显示dock时刷新或者
                实时监控中心窗体的改变（此方法之前试过，没有效果，可能是方法
                不对））（已解决：实时监听中心窗体的改变，然后刷新，更新控件
                位置）
             7、toolbar存储使用的map容器因为有自动排序功能，导致每次显示的toolbar
                初始位置会改变（不使用map，改成deque+结构体的形式）（已解决）
             8、sideBar的导航栏按钮文本是三个字是高度不够；(原因，按钮paint的时候
                文本高度没有设置够，已解决，并添加了设置按钮高度的接口)
             9、checkaction的信号发送有问题，触发不了；(已解决，采用信号传信号的方式传出封装的
                stateChanged信号，但是之前使用qt4的信号槽方式时把SIGNAL写成了SLOT)
             10、toolbar位置判断有问题；
             11、dock取消标题栏；
             12、toolbar坐标保存（在窗口关闭时发送信号，存储当前工具栏位置到配置文件中，下次打开时
                 读取配置文件中工具栏位置并显示）
 */
class FramelessHelper;
class UiTitleWidget;
class SideBar;
class InfoStatusBar;
class ToolBar;
class SwitchBar;
class StatusBar;
class ScaleBar;
class DockWidget;
class UI_EXPORT UiMainWindow : public QMainWindow
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(UiMainWindow)

public:
    enum UiStyle
    {
        Light,       //浅色
        Dark,       //黑色
        Default    //默认
    };
public:
    UiMainWindow(QWidget* parent = nullptr);
    ~UiMainWindow();

    //返回FramelessHelper
    FramelessHelper* framelessHelper();
    //覆写setCentralWidget(QWidget *widget);
    void setCentralWidget(QWidget* widget);
    //添加主按钮
    void setTitleIcon(const QIcon& icon, const qreal iconscale, QMenu* menu = nullptr);
    //设置标题
    void setWindowTitle(const QString& title);
    //设置标题字体
    void setTitleFont(const QFont& font);
    //获取标题字体
    QFont getTitleFont();
    //添加导航栏
    void setSideBar(SideBar* sideBar);
    //获取侧边导航栏
    SideBar* getSideBar();
    //设置状态栏
    void setInfoStatusBar(Ui::Corner loc, InfoStatusBar* statusBar);
    //设置开关栏
    void setSwitchBar(Ui::Corner loc, SwitchBar* switchBar);
    //设置比例尺
    void setScaleBar(ScaleBar* scaleBar);
    //设置底部状态栏
    void setStatusBar(StatusBar* bar);
    StatusBar* getStatuBar();
    //此函数仅用于控制最小最大化和关闭按钮的显示
    void updateWindowFlag(Qt::WindowFlags flags);
    //获取系统按钮的状态
    Qt::WindowFlags windowButtonFlags() const;
    //覆写addDockWidget
    void addDockWidget(Qt::DockWidgetArea area, DockWidget* dockwidget);
    QList<DockWidget*> getDockWidget();
    //设置ToolBar
    void setToolBar(Ui::ToolBarArea loc, ToolBar* toolbar);

    //设置样式
    void setStyle(UiStyle style);

protected:
    //覆写setMenuWidget
    void setMenuWidget(QWidget* menubar);
    void initOpenGL();
    //创建标题栏
    QWidget* createTitleBar();
    //加载样式
    void loadStyle(const QString& styleFile);
    //事件过滤器
    virtual bool eventFilter(QObject* obj, QEvent* e) Q_DECL_OVERRIDE;
    virtual void showEvent(QShowEvent* e);
    //void initToolBarLoc();
    ////刷新工具栏位置
    //void updateToolBarLoc();
    ////刷新开关栏位置
    //void updateSwitchBarLoc();
    ////刷新信息状态栏位置
    //void updateInfoStatusBarLoc();
    ////刷新比例尺位置
    //void updateScaleBarLoc();

protected slots:
    void showWidget(QWidget* widget);

signals:
    void signalCentralWidgetResize();
    void signalInitToolBarArea();
};

#endif  // UIMAINWINDOW_H
