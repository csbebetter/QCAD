#include "COMMAND.H"
#include "CCommandQrue.h"

CCommandQrue::CCommandQrue()
{
	m_curPos = 0;
}

CCommandQrue::~CCommandQrue()
{
	DeleteAll();
}

//ÿ�β�����ɺ���øú���
void CCommandQrue::AddCommands(CCommand* pCmd)
{
	assert(pCmd);

	AdjustCommands();
	m_vCommands.push_back(pCmd);
	m_curPos++;
}

//ÿ�β���֮ǰ���øú������������У�ɾȥ���ܵ��ڴ�
void CCommandQrue::AdjustCommands()
{
	if (m_curPos >= m_vCommands.count())
	{
		return;
	}

	//����������pcmd������Ǵ�����������ڴ棻��ɾȥ��pCmd
	for (int i = m_vCommands.count(); i > m_curPos ; i--)
	{
		CCommand* pCmd = m_vCommands.at(i);
		//����Ǵ���
		//if (pCmd->IsCreateCmd())
		//{
		//	QList<QGraphicsItem*> lstItems = pCmd->GetItems();
		//	foreach(QGraphicsItem * pItem, lstItems)
		//	{
		//		delete pItem;
		//	}
		//}
		m_vCommands.remove(i);
		delete pCmd;
	}
}

//���õ�ǰ��curPos�Ĳ�����ִ���� Undo
void CCommandQrue::Undo()
{
	CCommand* pCurCmd = m_vCommands.at(m_curPos);

	//pCurCmd->Undo();
	m_curPos--;
}

/*
*  �����������      Undo                        Redo
*  ����ʵ��          �Ƴ�ʵ�����ʾ�б�          ��ʵ���ټ�����ʾ�б�
*  �ƶ�/��ת/����    �����������ԭ��λ��        ִ�в��������¼����������ʵ�弯��
*  ɾ��              ��ʵ���ټ�����ʾ            �Ƴ�ʵ�����ʾ�б�
*  �����������塢���͡���ɫ��  ����Ҫ������������������ʵ�弯����Ӧʵ��Undo/redo
*/
void CCommandQrue::Redo()
{
	CCommand* pCurCmd = m_vCommands.at(m_curPos+1);

	//pCurCmd->Redo();
	m_curPos++;
}

//������ʵ�壬�����ɾ���������г��ǵ���������Ϊ��Undo/Redo��������ɾ��ʵ��
void CCommandQrue::DeleteAll()
{
	foreach(CCommand * pCmd, m_vCommands)
	{
		//����Ǵ���
		//if (pCmd->IsCreateCmd())
		//{
		//	QList<QGraphicsItem*> lstItems = pCmd->GetItems();
		//	foreach(QGraphicsItem * pItem, lstItems)
		//	{
		//		delete pItem;
		//	}
		//}
		delete pCmd;
	}

	m_vCommands.clear();
}
