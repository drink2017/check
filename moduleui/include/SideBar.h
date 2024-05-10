#ifndef SIDEBAR_H
#define SIDEBAR_H
#include "UiGlobal.h"
#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QToolBar>
/**
 * @brief 侧边导航栏
 *
 * @note 封装QToolBar，并且将toolbar固定在两侧来实现一个侧边栏
 * 
 * @todo 后续布局器要更该为QBoxLayout，不使用move的方式设置（已改，
         目前为在ToolBar中添加一个整体的widget，在widget中添加按钮
         控件以及布局）
 */
class UiSideToolButton;
class DockWidget;
class UI_EXPORT SideBar : public QToolBar
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(SideBar)
public:
    SideBar(QWidget* parent);
    ~SideBar();
    //添加导航按钮
    void addSideButton(QPushButton* sideBtn);
    //添加工具按钮
    void addSideToolButton(QWidget* widget, const QIcon& icon);
    //设置导航栏按钮高度
    void setToolButtonHeight(const int height);
    //获取绑定了的widget
    QList<QWidget*> getWidget();
    ////获取侧边导航栏按钮
    //QList<UiSideToolButton*> getSideToolButton();
    //覆盖sizeHint
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    //监听父窗口尺寸的改变
    virtual bool eventFilter(QObject* watched, QEvent* e) Q_DECL_OVERRIDE;

protected slots:
    void slotClickToolButton();

signals:
    void signal_dockWidgetButton_clicked(QWidget* widget);
};

/**
 * @brief 侧边栏按钮，用于绑定widget
 */
class UiSideToolButton : public QToolButton
{
    Q_OBJECT
public:
    UiSideToolButton(const QIcon& icon, const QString& name, QWidget* parent);
    //绑定widget
    void setWidget(QWidget* widget);
    //获取绑定的widget
    QWidget* getWidget();

protected:
    //重绘，实现字体纵向显示
    void paintEvent(QPaintEvent* event) override;

private:
    QWidget* mWidget;
};

#endif	//SIDEBAR_H