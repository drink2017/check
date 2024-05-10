#ifndef SCALEBAR_H
#define SCALEBAR_H
#include "UiGlobal.h"
#include <QWidget>

/**
 * @brief 比例尺
 *
 * @note 通过一个自定义上拉框和Label封装的比例尺
 */
class UI_EXPORT ScaleBar : public QWidget
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(ScaleBar)
public:
    ScaleBar(QWidget* parent = 0);
    ~ScaleBar();

    //添加上拉框item
    void addItem(const QString& text);
    //设置当前label中显示的文本
    void setCurrentText(const QString& text);
    //获取当前label中显示的文本
    QString getCurrentText();
    //覆盖sizeHint
    QSize sizeHint() const;
};

#endif	//SCALEBAR_H