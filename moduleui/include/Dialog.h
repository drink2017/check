#ifndef DIALOG_H
#define DIALOG_H
#include "UiGlobal.h"
#include "CommandDef.h"
#include <QDialog>
#include <QMenu>
/**
 * @brief 弹窗类
 *
 * @note 自定义封装标题栏，弹窗有两种类型，命令弹窗和普通弹窗；
 * 
 * @todo 后续3d部分需要加一个属性面板类型
 *		 
 */
class UI_EXPORT Dialog : public QDialog
{
	Q_OBJECT
	UI_DECLARE_PRIVATE(Dialog)
public:
	//type：弹窗类型（comd命令面板和general普通面板）
	Dialog(Ui::DialogType type, QWidget* parent = nullptr);
	~Dialog();

	//设置主按钮
	void setTitleIcon(const QString& icon, const qreal iconscale = 1);
	//设置标题
	void setWindowTitle(const QString& title);
	//设置标题字体
	void setTitleFont(const QFont& font);
	//获取标题字体
	QFont getTitleFont();
	//获取dialog中widget的布局器
	QLayout* getLayout() const;
	//设置布局器
	void setLayout(QLayout*);

protected:
    //事件过滤器
    virtual bool eventFilter(QObject* obj, QEvent* e) Q_DECL_OVERRIDE;

private slots:
	void closeWindow();

signals:
	void signalHide();
};

#endif	//DIALOG_H