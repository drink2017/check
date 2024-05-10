#ifndef MAINBUTTON_H
#define MAINBUTTON_H
#include "UiGlobal.h"
#include <QToolButton>

/**
 * @brief 标题栏图标主按钮
 *
 * @note 封装QToolButton实现点击图标弹出下拉菜单
 */
class MainButton : public QToolButton
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(MainButton)
public:
    MainButton(QWidget* parent = Q_NULLPTR);
    ~MainButton();

    //最小尺寸提示
    virtual QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    //设置按钮logo图片（图标，图标比例）
    void setMainIcon(const QIcon& icon, const qreal iconscale);

protected:
    virtual void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
};

#endif  // MAINBUTTON_H