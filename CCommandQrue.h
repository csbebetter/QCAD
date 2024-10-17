#pragma once

#include <QVector>
class CCommand;
//�������У����ڼ�¼�������޸�ͼԪʵ��Ĳ�������
//����������ʱ���½����������˳�ʱ��ɾ��
//ÿ�δ���ʵ��ʱ���������У�ÿ�β���ʱ���������У�����ɾ����
//
/*
 Command����ʵ��ָ�룬������������������Ҫ����Undo,Redo
*/
class CCommandQrue  //Ӧ�� queue
{
private:
	unsigned int m_curPos; //��¼��ǰλ�ã�����Undo/Redo
	QVector<CCommand*> m_vCommands;  //ȫ���Ĳ�������

public:
	CCommandQrue();
	~CCommandQrue();

public:
	void Undo(); //����
	void Redo(); //����
	
	void AddCommands(CCommand* pCmd);  //�����������
	void AdjustCommands();   //�������У������������ȥ����������Ҫɾ��ʵ��
	void DeleteAll();        //ɾ��ȫ���������У�����ɾ��ʵ���ڴ�
};
