#ifndef COMMANDDEF_H
#define COMMANDDEF_H
#include <qglobal.h>
#include <QObject>
/*
	定义一些常用枚举类
*/
namespace Ui
{
	Q_NAMESPACE

		//标题栏类型
		enum TitleBarType
	{
		MainWindowTitleBar = 0,
		ComdDialogTitleBar = 1,
		GeneralDialogTitleBar = 2
	};
	Q_ENUMS(TitleBarType)

		//弹窗类型
		enum DialogType
	{
		ComdDialog,			//命令面板
		GeneralDialog			//普通面板
	};
	Q_ENUMS(DialogType)

		//树节点类型
		enum TreeItemType
	{
		GeneralTreeItem,
		CheckTreeItem,
		ButtonTreeItem
	};
	Q_ENUMS(TreeItemType)

		//工具栏位置
		enum ToolBarArea
	{
		LeftToolBarArea = 0x1,
		RightToolBarArea = 0x2,
		TopToolBarArea = 0x4,
		BottomToolBarArea = 0x8,
		NoToolBarArea = 0
	};
	Q_ENUMS(ToolBarArea)

		//开关栏位置
		enum Corner
	{
		TopLeftCorner = 0x00000,
		TopRightCorner = 0x00001,
		BottomLeftCorner = 0x00002,
		BottomRightCorner = 0x00003,
		NoCorner = 0
	};
	Q_ENUMS(SwitchBarLoc)
}

#endif	//COMMANDDEF_H