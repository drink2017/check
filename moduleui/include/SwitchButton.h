#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

/**
 * 1:可设置开关按钮的样式 圆角矩形/内圆形/外圆形/图片
 * 2:可设置选中和未选中时的背景颜色
 * 3:可设置选中和未选中时的滑块颜色
 * 4:可设置显示的文本
 * 5:可设置滑块离背景的间隔
 * 6:可设置圆角角度
 */
#include "UiGlobal.h"
#include <QWidget>
enum ButtonStyle {
    ButtonStyle_Rect = 0,     //圆角矩形
    ButtonStyle_CircleIn = 1, //内圆形
    ButtonStyle_CircleOut = 2,//外圆形
    ButtonStyle_Image = 3,    //图片
    ButtonStyle_RectOut = 4,  //外矩形
};
class QTimer;

class UI_EXPORT SwitchButton : public QWidget
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(SwitchButton)
public:

    SwitchButton(QWidget* parent = 0);
    ~SwitchButton();

protected:
    void mousePressEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);

public:
    bool getChecked() const;
    ButtonStyle getButtonStyle() const;

    QColor getBgColorOff() const;
    QColor getBgColorOn() const;

    QColor getBgBorderColorOff() const;
    QColor getBgBorderColorOn() const;

    QColor getSliderColorOff() const;
    QColor getSliderColorOn() const;

    QColor getSliderBorderColorOff() const;
    QColor getSliderBorderColorOn() const;

    QColor getTextColorOff() const;
    QColor getTextColorOn() const;

    QString getTextOff() const;
    QString getTextOn() const;

    QString getImageOff() const;
    QString getImageOn() const;

    int getSpace() const;
    int getRectRadius() const;

    //设置是否选中
    void setChecked(bool checked);
    //设置风格样式
    void setButtonStyle(ButtonStyle buttonStyle);

    //设置背景颜色
    void setBgColor(QColor bgColorOff, QColor bgColorOn);
    //设置背景颜色
    void setBgBorderColor(QColor bgBorderColorOff, QColor bgBorderColorOn);
    //设置滑块颜色
    void setSliderColor(QColor sliderColorOff, QColor sliderColorOn);
    //设置滑块颜色
    void setSliderBorderColor(QColor sliderBorderColorOff, QColor sliderBorderColorOn);
    //设置文本颜色
    void setTextColor(QColor textColorOff, QColor textColorOn);

    //设置文本
    void setText(QString textOff, QString textOn);

    //设置背景图片
    void setImage(QString imageOff, QString imageOn);

    //设置间隔
    void setSpace(int space);
    //设置圆角角度
    void setRectRadius(int rectRadius);

private slots:
    void updateValue();

signals:
    void checkedChanged(bool checked);
};

#endif // SWITCHBUTTON_H