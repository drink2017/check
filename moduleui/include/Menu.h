#ifndef MENU_H
#define MENU_H
#include "UiGlobal.h"
#include <QMenu>

/**
 * @brief 菜单，用于下拉菜单，右键菜单
 *
 * @note 封装QMenu，可以设置icon的尺寸
 */
class UI_EXPORT Menu : public QMenu
{
    Q_OBJECT
    UI_DECLARE_PRIVATE(Menu)
public:
    explicit Menu(QWidget* parent = nullptr);
    explicit Menu(const QString& title, QWidget* parent = nullptr);
    ~Menu();
    //设置图标大小
    void setIconSize(const int& size);
};

#endif	//MENU_H