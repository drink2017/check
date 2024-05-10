#ifndef TITLEBAR_H
#define TITLEBAR_H
#include "UiGlobal.h"
#include "CommandDef.h"
#include <QWidget>
#include <QLabel>
#include <QMenu>

/**
 * @brief 标题栏
 *
 * @note 封装图标主按钮，放大缩小关闭按钮组和标题标签
 * 
 * @todo 后续使用间隔控件将标题栏重新布局(已改)
 *       1、新增主窗口标题栏，命令窗口标题栏，一般弹窗标题栏,dock窗口标题栏
 */
class UI_EXPORT TitleBar : public QWidget
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(TitleBar)

public:
    TitleBar(QWidget* parent);
    ~TitleBar();

    //此函数仅用于控制最小最大化和关闭按钮的显示
    void updateWindowFlag(Qt::WindowFlags flags);

    //获取系统按钮的状态
    Qt::WindowFlags windowButtonFlags() const;
    //设置主按钮
    void setTitleIcon(const QIcon& icon, const qreal iconscale, QMenu* menu = nullptr);
    //设置标题
    void setWindowTitle(const QString& title);
    //设置标题字体
    void setTitleFont(const QFont& font);
    //获取标题字体
    QFont getTitleFont();
    //重写sizeHint
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    //监听父窗口的尺寸变化
    virtual bool eventFilter(QObject* watched, QEvent* e) Q_DECL_OVERRIDE;
    virtual void parentResize();

signals:
    void signalWindowClose();
};

/**
 * @brief 封装标题label
 */
class UiWindowTitleLabel : public QLabel
{
    Q_OBJECT
public:
    UiWindowTitleLabel(QWidget* p = nullptr);
};

#endif  // TITLEBAR_H