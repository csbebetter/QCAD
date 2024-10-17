#include "MCreateLine.h"
#include "mainwindow.h"
#include "QCADView.h"
#include "ENTITY.H"

//#include <QRubberBand>
#include <QMouseEvent>

MCreateLine::MCreateLine(QCADView* pDiagramScene)
	: m_begin(0, 0), m_end(0, 0)
{
	m_nStep = 0; // ��ʼ��������Ϊ 0
	m_pDC = pDiagramScene;

	//rubberBand = NULL;
}

MCreateLine::~MCreateLine()
{
}

int MCreateLine::GetType()
{
	return ctCreateLine;
}

int	MCreateLine::OnLButtonDown(QMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return 0;

	QPen pen(m_pDC->penStyle());   
	pen.setColor(m_pDC->lineColor());  
	pen.setWidthF(m_pDC->penWidth());

	m_nStep++; // ÿ�ε���������ʱ�������� 1 

	switch (m_nStep) // ���ݲ�����ִ����Ӧ�Ĳ���
	{
	case 1:
	{
		m_begin = m_end = m_tempPos = mouseEvent->pos();
		
		//rubberBand = new QRubberBand(QRubberBand::Line, m_pDC);
		m_pLine = new MLine(m_begin, m_end);
		m_pLine->SetPen(pen);
		m_pDC->addEntity(m_pLine);

		QString sPrmt = QStringLiteral("������ֱ�ߵ���һ�㣺");
		Prompt(sPrmt);
		break;
	}
	case 2:
	{
		m_end = mouseEvent->pos();

		//m_pDC->update();

		//rubberBand->hide();
		//delete rubberBand;
		//rubberBand = NULL;

		m_nStep = 0;

		//// ����ڰ��������Ĺ�����ͬʱ������Shift����
		////	��ô������굥��λ�û���ˮƽ�߻���ֱ��
		//if( nFlags & MK_SHIFT ){ 
		//	double dx = pos.x - m_begin.x;
		//	double dy = pos.y - m_begin.y;
		//	if(fabs(dx) <= fabs(dy)) // �����굥��λ����X���򿿽����
		//		m_end.Set(m_begin.x, pos.y); // ��ô�յ��x������������ͬ
		//	else
		//		m_end.Set(pos.x,m_begin.y);
		//}
		//else if (m_bCaptured)
		//{
		//	m_end = m_ptCapture;
		//}
		//else {
		//	m_end = pos; // ���δ����Shift��, ���յ�Ϊ��굥��λ��			
		//}
		break;
	}
	default:
		break;
	}

	return 0;
}

//������˫����������ʹ�ã��˴�ֻ��������ֱ��
int MCreateLine::OnLButtonDblClk(QMouseEvent* mouseEvent)
{
	//// �������϶�״̬ʱ��ʾ�����һ����
	//MLines*	pTempLine = new MLines(m_begin,m_end); 
	//pTempLine->Draw(pDC, dmDrag);
	//delete pTempLine;
	//
	//// ����ڰ��������Ĺ�����ͬʱ������Shift����
	////	��ô������굥��λ�û���ˮƽ�߻���ֱ��
	//if( nFlags & MK_SHIFT ){ 
	//	double dx = pos.x - m_begin.x;
	//	double dy = pos.y - m_begin.y;
	//	if(fabs(dx) <= fabs(dy)) // �����굥��λ����X���򿿽����
	//		m_end.Set(m_begin.x, pos.y); // ��ô�յ��x������������ͬ
	//	else
	//		m_end.Set(pos.x,m_begin.y);
	//}
	//else
	//	m_end = pos; // ���δ����Shift��, ���յ�Ϊ��굥��λ��			
	//
	//if(m_nStep >= 2) {
	//	MLines*	pNewLine = new MLines(m_pPositions);// ���������յ㴴��ֱ��
	//	pNewLine->Draw(pDC,dmNormal); // ����ֱ��
	//	g_pDoc->m_EntityList.AddTail(pNewLine); // ��ֱ��ָ����ӵ�ͼԪ����
	//	g_pDoc->SetModifiedFlag(TRUE);// set modified flag ;
	//	pNewLine->m_nOperationNum = g_pView->m_nCurrentOperation;
	//	m_pPositions.clear();
	//}
	//
	//g_pView->ReleaseDC(pDC); // �ͷ��豸����ָ��
	//
	//m_nStep = 0;  // ������������Ϊ 0
	//Prompt(QStringLiteral(""������ֱ�ߵ���㣺");

	return 0;
}

int	MCreateLine::OnMouseMove(QMouseEvent* mouseEvent)
{
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAW_LINE));

	MCommand::OnMouseMove(mouseEvent);

	switch (m_nStep)
	{
	case 0:
		::Prompt(QStringLiteral("������ֱ�ߵ���㣺"));
		break;
	default:
	{
		//// ����ڰ��������Ĺ�����ͬʱ������Shift����
		////	��ô������굥��λ�û���ˮƽ�߻���ֱ��
		//if( nFlags & MK_SHIFT ){
		//	double dx = pos.x - m_begin.x;
		//	double dy = pos.y - m_begin.y;
		//	if(fabs(dx)>=fabs(dy))
		//		curPos.Set(pos.x,m_begin.y);
		//	else
		//		curPos.Set(m_begin.x, pos.y);
		//}
		//else if (m_bCaptured)
		//{
		//	curPos = m_ptCapture;
		//}
		//else {
		//	curPos = pos; // ���δ����Shift��, ���յ�Ϊ��굥��λ��			
		//}
		
		QPointF curPos = mouseEvent->pos();

		m_pLine->SetEndPos(curPos);
		m_pDC->update();

		////�������ģʽ����ȥ�ϴε���Ƥ��
		////QLineF oldLine(m_begin, m_tempPos);
		//QPainter paintDC(m_pDC);
		//paintDC.drawLine(m_begin, m_tempPos);

		////��������ģʽ����ʾ��λ�õ���Ƥ��
		//QLineF newLine(m_begin, curPos);
		//paintDC.drawLine(newLine);

		int aLeft = m_begin.x();
		int aTop = m_begin.y();
		int aWide = curPos.x() - m_begin.x();
		int aHeight = curPos.y() - m_begin.y();
		QRect rect(aLeft, aTop, aWide, aHeight );

		//if (rubberBand)
		//{
		//	rubberBand->setGeometry(rect);
		//	rubberBand->show();
		//}
		break;
	}
	}

	return 0;
}

// ��������Ҽ�ȡ����ǰ�Ĳ���
int	MCreateLine::OnRButtonDown(QMouseEvent* mouseEvent)
{
	Cancel();
	//// �����ǰ�Ĳ�����Ϊ 1 ����ôҪ�ڽ������β���ǰ�����ϴ�����ƶ�ʱ���Ƶ���Ƥ��
	//if(m_nStep == 1){ 
	//	CDC*	pDC = g_pView->GetDC(); // �õ��豸����ָ��
	//	QPointF	prePos = m_end; // ���������ڵ�ǰһ��λ��
	//	MLines*	pTempLine = new MLines(m_begin, prePos); 
	//	pTempLine->Draw(pDC, dmDrag); // ������һ�λ��Ƶ���Ƥ��
	//	delete pTempLine;
	//	g_pView->ReleaseDC(pDC); // �ͷ��豸����ָ��
	//}
	//m_nStep = 0; // ������������Ϊ 0 
	//Prompt(QStringLiteral(""������ֱ�ߵ���㣺");
	return 0;
}
// ����Cancel ����ȡ�����β���
int MCreateLine::Cancel()
{
	// �����ǰ�Ĳ�����Ϊ 1 ����ôҪ�ڽ������β���ǰ�����ϴ�����ƶ�ʱ���Ƶ���Ƥ��
	if (m_nStep == 1) {
		//m_pDiagramScene->removeItem(m_pLine);
	}

	m_nStep = 0; // ������������Ϊ 0 
	Prompt(QStringLiteral("������ֱ�����...")); // �ȴ���ʾ�����͵��������
	return 0;
}


