#ifndef STATUSBAR_H
#define STATUSBAR_H
#include "UiGlobal.h"
#include <QSTatusBar>

class UI_EXPORT StatusBar : public QStatusBar
{
	Q_OBJECT
public:
	StatusBar(QWidget* parent = nullptr);
	~StatusBar();
};

#endif	//STATUSBAR_H