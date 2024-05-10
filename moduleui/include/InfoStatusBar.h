#ifndef INFOSTATUSBAR_H
#define INFOSTATUSBAR_H
#include "UiGlobal.h"
#include "CommandDef.h"
#include <QFrame>
#include <QBoxLayout>

/**
 * @brief 状态栏
 *
 * @note 可添加自定义控件，或添加标签
 * 
 * @todo 后续删除设置控件位置
 */
class UI_EXPORT InfoStatusBar : public QFrame
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(InfoStatusBar)
public:
    InfoStatusBar(QWidget* parent);
    ~InfoStatusBar();

    //添加状态栏控件
    void addStatusWidget(QWidget* widget);
    //pramName：状态名称，pram：状态参数，pramLen状态参数标签宽度
    void addStatusWidget(const QString& pramName, const QString& pram, const int& pramLen);

    void updateStatus(const QString& pramName, const QString& pram);

    //获取布局器
    QBoxLayout* layout();

    //重写sizeHint
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    virtual bool eventFilter(QObject* watched, QEvent* e) Q_DECL_OVERRIDE;
};
#endif  //INFOSTATUSBAR_H