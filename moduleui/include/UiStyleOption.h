#pragma once
#include "UiGlobal.h"
/**
 * @brief 定义了ui所有尺寸相关信息，ui的建立都基于此类的尺寸，如果想调整，
 * 可以通过 @ref UiElementCreateDelegate（通过UiElementManager单例管理） 的 @ref UiStyleOption 函数设置自己的UiStyleOption
 *
 * @note 此类定义了ui的控件尺寸
 *
 * @todo 后续开发此类仅在ui库内部使用，外部需要修改尺寸需要在修改配置文件，后续控件会提供调用此类的接口，
 *       具体逻辑为：此类提供修改尺寸的接口->控件对此类的提供的接口进行封装再提供给外部->外部调用控件提供的接口实现修改
 */
class UiStyleOption
{
public:
    UiStyleOption();
    virtual ~UiStyleOption();

public:
    //主窗口标题栏的高度
    virtual int windowTitleBarHeight() const;
    //弹窗和命令标题栏的高度
    virtual int dialogTitleBarHeight() const;
    //导航栏宽度
    virtual int sideBarWidth() const;
    //横向时工具栏高度
    virtual int toolBarHeight() const;
    //dock标题栏高度
    virtual int dockTitleBarHeight() const;
    //dock工具栏高度
    virtual int dockToolBarHeight() const;

private:
    //初始化
    void init();

private:
    int m_windowTitleBarHeight;                      ///< 主窗口标题栏高度
    int m_dialogTitleBarHeight;                      ///< 弹窗和命令标题栏高度
    int m_sideBarWidth;                       ///< 导航栏宽度
    int m_toolBarHeight;                     ///<工具栏高度
    int m_dockTitleBarHeight;               ///<dock标题栏高度
    int m_dockToolBarHeight;               ///<dock工具栏高度
};