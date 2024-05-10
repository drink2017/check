#ifndef UIGLOBAL_H
#define UIGLOBAL_H
#include <qglobal.h>
#include <memory>
#include <QWidget>

#ifndef UI_NO_EXPORT
#if defined(UI_MAKE_LIB)  // 定义此宏将构建library
#define UI_EXPORT Q_DECL_EXPORT
#else
#define UI_EXPORT Q_DECL_IMPORT
#endif
#endif

#ifndef UI_EXPORT
#define UI_EXPORT
#endif

/**
 * @def   模仿Q_DECLARE_PRIVATE，但不用前置声明而是作为一个内部类
 */
#ifndef UI_DECLARE_PRIVATE
#define UI_DECLARE_PRIVATE(classname)                                                                           \
    class PrivateData;                                                                                                 \
    friend class classname::PrivateData;                                                                               \
    std::unique_ptr< PrivateData > d_ptr;
#endif
 /**
  * @def   模仿Q_DECLARE_PUBLIC
  */
#ifndef UI_DECLARE_PUBLIC
#define UI_DECLARE_PUBLIC(classname)                                                                            \
    friend class classname;                                                                                            \
    classname* q_ptr { nullptr };
#endif

#endif  // UIGLOBAL_H