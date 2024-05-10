#ifndef COMDBUTTON_H
#define COMDBUTTON_H
#include "UiGlobal.h"
#include <QPushButton>

/*
* 命令面板中使用的按钮，对qpushbutton进行封装，方便设置样式
*/
class UI_EXPORT ComdButton : public QPushButton
{
	Q_OBJECT
public:
    ComdButton(QWidget* parent = nullptr);
    ComdButton(const QString& text, QWidget* parent = nullptr);
    ComdButton(const QIcon& icon, const QString& text, QWidget* parent = nullptr);
    ~ComdButton();
};

#endif	//COMDBUTTON_H