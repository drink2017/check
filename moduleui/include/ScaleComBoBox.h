#ifndef SCALECOMBOBOX_H
#define SCALECOMBOBOX_H
#include "UiGlobal.h"
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QToolButton>
/**
 * @brief 比例尺下拉框
 *
 * @note 自定义下拉框，实现点击label显示拉框，并显示在label上方，
 *       点击锁定按钮后(此处不确定是锁定下拉框还是锁定当前比例值)，
 *       点击下拉框中item能够更改label中的值
 */

class ScaleComBoBox : public QWidget
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(ScaleComBoBox)
public:
    ScaleComBoBox(QWidget* parent = 0);
    ~ScaleComBoBox();

    //添加下拉框中的item
    void addItem(const QString& text);
    //设置当前label显示值
    void setCurrentText(const QString& text);
    //获取当前label显示值
    QString getCurrentText();
    //覆盖sizeHint，获取窗体大小
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    //实现label点击弹出下拉框事件
    bool eventFilter(QObject* watched, QEvent* event);

protected slots:
    void slotLockClicked();
    void slotItemClicked(QListWidgetItem* item);

};

/**
 * @brief 锁定按钮封装
 */
class LockButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(bool lock READ getLock WRITE setLock)    //自定义状态（qss中设置样式使用）
public:
    LockButton(QWidget* parent = nullptr);
    //获取当前是否锁定
    bool getLock();
    //设置当前是否锁定
    void setLock(bool value);

private:
    bool lock = false;
};

#endif  //SCALECOMBOBOX_H