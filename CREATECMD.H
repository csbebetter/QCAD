#ifndef _CreateCmd_h_
#define _CreateCmd_h_

#include <QVector>
#include "COMMAND.H"

/*********/
#include <QGraphicsLineItem>

#ifdef __cplusplus

class QGraphicsLineItem;
class QGraphicsEllipseItem;
class QGraphicsPathItem;
class QGraphicsRectItem;
class QGraphicsPolygonItem;
///////////////////////////////////////////////////////////////
/*	
 *	CCreateLine
 */
class CCreateLine : public CCommand
{
private:
	QPointF m_begin;	// 直线的起点
	QPointF m_end;		// 直线的终点 
	std::vector<QPointF> m_pPositions;
	QGraphicsLineItem* m_pLine;

public:
	CCreateLine(DiagramScene* pDiagramScene) ;
	~CCreateLine() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent);
	int		OnLButtonDblClk(QGraphicsSceneMouseEvent* mouseEvent);
	int		Cancel() ;
} ;

///////////////////////////////////////////////////////////////
/*	
 *	CCreateConnect
 */
class CCreateConnect : public CCommand
{
private:
	QPointF m_begin;	// 直线的起点
	QPointF m_end;		// 直线的终点 
	QPointF *m_pPositions;
	int		 m_bImport; //1, Im, -1, Out, 0 else
public:
	CCreateConnect() ;
	~CCreateConnect() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent);
	int		OnLButtonDblClk(QGraphicsSceneMouseEvent* mouseEvent);
	int		Cancel() ;
} ;

/*
 *	CCreatePolygon
 */
class CCreatePolygon : public CCommand
{
private:
	QPointF m_begin;	// 起点
	QPointF m_end;		// 临时终点 
	QVector<QPointF>    m_pPositions;
	QGraphicsPolygonItem* m_pPolygon;
	QVector<QGraphicsLineItem*> m_pTempLines;
	QGraphicsLineItem*  m_pTempLine;
public:
	CCreatePolygon(DiagramScene* pDiagramScene) ;
	~CCreatePolygon() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent);
	int		OnLButtonDblClk(QGraphicsSceneMouseEvent* mouseEvent);
	int		Cancel() ;
} ;

///////////////////////////////////////////////////////////////
/*	
 *	CCreateRect
 */
class CCreateRect : public CCommand
{
private:
	QPointF m_LeftTop;
	QPointF m_RightBottom;
	QGraphicsRectItem* m_pRect;
public:
	CCreateRect(DiagramScene* pDiagramScene) ;
	~CCreateRect() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;

	int		Cancel() ;
} ;


///////////////////////////////////////////////////////////////
/*	
 *	CCreateText
 */
class CCreateText : public CCommand
{
private:
	QPointF m_LeftTop;
	QPointF m_RightBottom;
public:
	CCreateText() ;
	~CCreateText() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnLButtonDblClk(QGraphicsSceneMouseEvent* mouseEvent) ;

	int		Cancel() ;
} ;
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/*	
 *	CCreateBlock
 */
class CCreateBlock : public CCommand
{
private:
	QPointF m_LeftTop;
	QPointF m_RightBottom;
public:
	CCreateBlock() ;
	~CCreateBlock() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnLButtonDblClk(QGraphicsSceneMouseEvent* mouseEvent) ;

	int		Cancel() ;
} ;
///////////////////////////////////////////////////////////////
/*	
 *	CCreateArc
 */
class CCreateCircle : public CCommand
{
private:
	QPointF	m_center ;
	QPointF	m_pos ;
	QGraphicsEllipseItem* m_pCircle;
	QGraphicsLineItem* m_pTempLine;
public:
	CCreateCircle(DiagramScene* pDiagramScene) ;
	~CCreateCircle() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;

	int		Cancel() ;
} ;

///////////////////////////////////////////////////////////////
/*	
 *	CCreateEllipse
 */
class CCreateEllipse : public CCommand
{
private:
	QPointF	m_LeftTop ;
	QPointF	m_RightBottum ;
	QGraphicsEllipseItem* m_pEllipse;
public:
	CCreateEllipse(DiagramScene* pDiagramScene) ;
	~CCreateEllipse() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;

	int		Cancel() ;
} ;

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/*	
 *	CCreateArc
 */
class CCreateArc : public CCommand
{
private:
	QPointF m_center;
	QPointF m_begin;
	QPointF m_end ;
	QGraphicsPathItem* m_pArc;
	QGraphicsLineItem* m_pLineItem;

public:
	CCreateArc(DiagramScene* pDiagramScene) ;
	~CCreateArc() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;

	int		Cancel() ;
} ;

///////////////////////////////////////////////////////////////
/*	
 *	CCreateFitCurve
 */
class CCreateFitCurve : public CCommand
{
private:
	QPointF m_begin;	// 直线的起点
	QPointF m_end;		// 直线的终点 
	QPointF *m_pPositions;

	int m_nCmd;
public:
	CCreateFitCurve(int nCmd) ;
	~CCreateFitCurve() ;

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent) ;
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent);
	int		OnLButtonDblClk(QGraphicsSceneMouseEvent* mouseEvent);
	int		Cancel() ;
} ;


///////////////////////////////////////////////////////////////
/*
 *	创建尺寸标注dimension
 */
class CREATEDIMENSION : public CCommand
{
public:
	enum DimensionType	// 尺寸标注处理的几何类
	{
		DimNull = 0,

		DimLine = 1,		// 直线段
		DimRectangle = 2,	// 矩形
		DimEllipse = 3,		// 圆or椭圆
	};

	enum DimensionDirection 
	{
		DimHorizontal=0,  //水平标注标志
		DimVertical=1     //竖直标注标志
	};

	void setDimensionDirection(DimensionDirection direction);
	QGraphicsPolygonItem* leftArrow = nullptr;  // 左侧箭头
	QGraphicsPolygonItem* rightArrow = nullptr;  // 右侧箭头
	QGraphicsPolygonItem* topArrow = nullptr;  // 左侧箭头
	QGraphicsPolygonItem* bottomArrow = nullptr;  // 右侧箭头

private:
	QPointF m_begin;	// 直线的起点
	QPointF m_end;		// 直线的终点 
	QGraphicsLineItem* m_pTempLine;  // 临时线条
	QGraphicsLineItem* m_pTempLineH1;  // 临时线条(水平标注时竖着的线1)
	QGraphicsLineItem* m_pTempLineH2;  // 临时线条(水平标注时竖着的线2)
	QGraphicsLineItem* m_pTempLineV1;  // 临时线条(竖直标注时横着的线1)
	QGraphicsLineItem* m_pTempLineV2;  // 临时线条(竖直标注时横着的线2)
	QGraphicsItem* m_pSelItem;       // 选中的图元
	QGraphicsTextItem* horizontalText; //水平文本
	QGraphicsTextItem* verticalText;   // 竖直文本
	DimensionType dimType;
	DimensionDirection m_dimDirection; // 方向判断标志


public:
	CREATEDIMENSION(DiagramScene* pDiagramScene);
	~CREATEDIMENSION();

	/*void setDimensionDirection(DimensionDirection direction);*/

	int		GetType();
	int		OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent);
	int		OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent);
	int		OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent);
	//int		OnLButtonDblClk(QGraphicsSceneMouseEvent* mouseEvent);
	int		Cancel();

	int     DrawHorizontalDimension(const QPointF& start, const QPointF& end);
	int     DrawVerticalDimension(const QPointF& start, const QPointF& end);
};





#endif // #ifdef __cplusplus

#endif