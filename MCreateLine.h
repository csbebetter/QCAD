#pragma once
#include "MCommand.h"

class MLine;

class MCreateLine :
    public MCommand
{
private:
	QPointF m_begin;	// ֱ�ߵ����
	QPointF m_end;		// ֱ�ߵ��յ� 
	QPointF m_tempPos; //��ʱ��
	MLine*  m_pLine;

public:
	MCreateLine(QCADView* pDiagramScene);
	~MCreateLine();

	int		GetType();
	int		OnLButtonDown(QMouseEvent* mouseEvent);
	int		OnMouseMove(QMouseEvent* mouseEvent);
	int		OnRButtonDown(QMouseEvent* mouseEvent);
	int		OnLButtonDblClk(QMouseEvent* mouseEvent);

	int		Cancel();
};

