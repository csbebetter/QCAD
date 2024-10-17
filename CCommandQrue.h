#pragma once

#include <QVector>
class CCommand;
//命令序列，用于记录创建，修改图元实体的操作过程
//主程序启动时，新建；主程序退出时，删除
//每次创建实体时，加入序列，每次操作时，加入序列（包括删除）
//
/*
 Command对象：实体指针，操作参数（创建不需要）；Undo,Redo
*/
class CCommandQrue  //应该 queue
{
private:
	unsigned int m_curPos; //记录当前位置，用于Undo/Redo
	QVector<CCommand*> m_vCommands;  //全部的操作序列

public:
	CCommandQrue();
	~CCommandQrue();

public:
	void Undo(); //撤销
	void Redo(); //重做
	
	void AddCommands(CCommand* pCmd);  //增加命令操作
	void AdjustCommands();   //整理序列，将多余的序列去除，可能需要删除实体
	void DeleteAll();        //删除全部命令序列，真正删除实体内存
};
