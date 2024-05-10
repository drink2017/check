#ifndef UIELEMENTMANAGER_H
#define UIELEMENTMANAGER_H
#include "UiElementFactory.h"
#include "UiGlobal.h"
/**
 * @brief 此类是一个全局单例，用于管理工厂
 *
 * @note 通过一个自定义上拉框和Label封装的比例尺
 */
class UI_EXPORT UiElementManager
{
protected:
    UiElementManager();

public:
    virtual ~UiElementManager();
    static UiElementManager* instance();
    UiElementFactory* factory();
    void setupFactory(UiElementFactory* fac);

private:
    QScopedPointer< UiElementFactory > mFactory;
};
#ifndef UiSubElementMgr
#define UiSubElementMgr UiElementManager::instance()
#endif
#ifndef UiSubElementDelegate
#define UiSubElementDelegate UiElementManager::instance()->factory()
#endif
#ifndef UiSubElementStyleOpt
#define UiSubElementStyleOpt UiElementManager::instance()->factory()->getUiStyleOption()
#endif
#endif  // UIELEMENTMANAGER_H

