#include "MSelectCmd.h"

#include "mainwindow.h"
#include "QCADView.h"
#include "ENTITY.H"

#include <QMouseEvent>
#include <QRubberband>

MSelectCmd::MSelectCmd(QCADView* pDiagramScene)
	: m_begin(0, 0), m_end(0, 0)
{
	m_nStep = 0; // ��ʼ��������Ϊ 0
	m_pDC = pDiagramScene;

	rubberband = NULL;
}

MSelectCmd::~MSelectCmd()
{
	delete rubberband;
}

int MSelectCmd::GetType()
{
	return ctSelect;
}

//�����ѡ��ʵ��ͽ���
//������������ѡ�񡣡���
int	MSelectCmd::OnLButtonDown(QMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return 0;

	//��ʼҪ�����Ƿ���shift�����£��������������ѡ��
	m_pDC->ClearSelections();

	m_nStep++; // ÿ�ε���������ʱ�������� 1 

	switch (m_nStep) // ���ݲ�����ִ����Ӧ�Ĳ���
	{
	case 1:
	{
		m_begin = m_end = mouseEvent->pos();

		//�����û��ѡ��ʵ��
		bool bSelected = false;
		QList<MEntity*> lstEntitys = m_pDC->GetEntityList();
		foreach(MEntity * pEnt, lstEntitys)
		{
			if (pEnt->Pick(m_begin, PICK_RADIUS))
			{
				m_pDC->AddSelection(pEnt);
				bSelected = true;
			}
		}
		if (bSelected)
		{
			m_pDC->update(); //ˢ����ʾѡ��

			m_nStep = 0;
			break;
		}
		
		rubberband = new QRubberBand(QRubberBand::Line, m_pDC);
		QString sPrmt = QStringLiteral("��ѡ������һ�㣺");
		Prompt(sPrmt);
		break;
	}
	case 2:
	{
		m_end = mouseEvent->pos();

		QList<MEntity*> lstEntitys = m_pDC->GetEntityList();
		foreach(MEntity * pEnt, lstEntitys)
		{
			//�˺�����Ҫʵ��.......
			if (0) //pEnt->IsInRect(m_begin, m_end))
			{
				m_pDC->AddSelection(pEnt);
			}
		}
		if (rubberband)
		{
			rubberband->hide();
			delete rubberband;
			rubberband = NULL;
		}
		m_pDC->update();

		m_nStep = 0;
		break;
	}
	default:
		break;
	}

	return 0;
}

//������˫����������ʹ�ã��˴�ֻ��������ֱ��
int MSelectCmd::OnLButtonDblClk(QMouseEvent* mouseEvent)
{
	
	return 0;
}

int	MSelectCmd::OnMouseMove(QMouseEvent* mouseEvent)
{
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAW_LINE));

	MCommand::OnMouseMove(mouseEvent);

	switch (m_nStep)
	{
	case 0:
		::Prompt(QStringLiteral("ѡ��ʵ�壺"));
		break;
	default:
	{
		QPointF curPos = mouseEvent->pos();

		int aLeft = m_begin.x();
		int aTop = m_begin.y();
		int aWide = curPos.x() - m_begin.x();
		int aHeight = curPos.y() - m_begin.y();
		QRect rect(aLeft, aTop, aWide, aHeight);

		if (rubberband)
		{
			rubberband->setGeometry(rect);
			rubberband->show();
		}
		break;
	}
	}

	return 0;
}

// ��������Ҽ�ȡ����ǰ�Ĳ���
int	MSelectCmd::OnRButtonDown(QMouseEvent* mouseEvent)
{
	Cancel();
	//// �����ǰ�Ĳ�����Ϊ 1 ����ôҪ�ڽ������β���ǰ�����ϴ�����ƶ�ʱ���Ƶ���Ƥ��

	return 0;
}
// ����Cancel ����ȡ�����β���
int MSelectCmd::Cancel()
{
	// �����ǰ�Ĳ�����Ϊ 1 ����ôҪ�ڽ������β���ǰ�����ϴ�����ƶ�ʱ���Ƶ���Ƥ��
	if (m_nStep == 1) {
		//m_pDiagramScene->removeItem(m_pLine);
	}

	m_nStep = 0; // ������������Ϊ 0 
	return 0;
}

