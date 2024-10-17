#include "math.h"
#include "Command.h"
#include "CreateCmd.h"

#include "diagramscene.h"

#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QRectF>
#include <QtWidgets>
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////



CREATEDIMENSION::CREATEDIMENSION(DiagramScene* pDiagramScene)
	: m_begin(0, 0), m_end(0, 0)
{
	leftArrow = nullptr;
	rightArrow = nullptr;
	m_nStep = 0; // 初始化操作步为 0
	m_pDiagramScene = pDiagramScene;
	dimType = DimNull;
	m_pSelItem = NULL;
	if (m_pDiagramScene->selectedItems().count() > 0)
	{
		m_pSelItem = m_pDiagramScene->selectedItems().first();
		// 检查选中的项是否是 QGraphicsLineItem
		QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(m_pSelItem);
		QGraphicsRectItem* rectItem = dynamic_cast<QGraphicsRectItem*>(m_pSelItem);
		QGraphicsEllipseItem* ellipseItem = dynamic_cast<QGraphicsEllipseItem*>(m_pSelItem);
		if (lineItem) {
			dimType = DimLine;
			// 获取 QLineF 对象，它包含了直线的两个端点
			QLineF line = lineItem->line();

			// 获取直线的起点和终点坐标
			m_begin = line.p1();
			m_end = line.p2();
			//QString sScreenPosX = QString::number(m_begin.x(), 'f', 2);
			//QString sScreenPosY = QString::number(m_begin.y(), 'f', 2);
			//QString sScnPos = QStringLiteral("直线坐标：");
			//sScnPos += sScreenPosX;
			//sScnPos += ", ";
			//sScnPos += sScreenPosY;
			//Prompt(sScnPos);

		}
		else if (rectItem)
		{
			dimType = DimRectangle;

			// 获取椭圆的矩形范围
			QRectF rect = rectItem->rect();

			// 获取椭圆的起点和终点坐标
			m_begin = rect.topLeft();
			m_end = rect.bottomRight();
		}
		else if (ellipseItem) {
			dimType = DimEllipse;
			
			// 获取椭圆的矩形范围
			QRectF ellipseRect = ellipseItem->rect();

			// 获取椭圆的起点和终点坐标
			m_begin = ellipseRect.topLeft();
			m_end = ellipseRect.bottomRight();

		}
	}

}

CREATEDIMENSION::~CREATEDIMENSION()
{
	
}

int CREATEDIMENSION::GetType()
{
	return m_dimDirection == DimVertical ? ctVerticalDimension : ctHorizontalDimension;
}


void CREATEDIMENSION::setDimensionDirection(DimensionDirection direction)
{
    m_dimDirection = direction;
}

int	CREATEDIMENSION::OnLButtonDown(QGraphicsSceneMouseEvent* mouseEvent)
{
	m_nStep++;
	switch (m_nStep)
	{
	case 1:
	{

		switch (dimType)
		{
		case CREATEDIMENSION::DimNull:
		{
			break;
		}
			
		case CREATEDIMENSION::DimLine:  // 若此前已经选中直线，且已获取了直线两端点坐标
		{

			if (m_dimDirection == DimHorizontal)
			{
				// 设置水平标注线
				m_pTempLine = new QGraphicsLineItem;
				QPointF h_begin(m_begin.x(), mouseEvent->scenePos().y());
				QPointF h_end(m_end.x(), mouseEvent->scenePos().y());
				QLineF line(h_begin, h_end);


				// 创建一个 QPen 对象并设置颜色
				QPen pen;
				pen.setColor(Qt::blue);
				// 应用 QPen 到 QGraphicsLineItem
				m_pTempLine->setPen(pen);
				m_pTempLine->setLine(line);
				m_pDiagramScene->addItem(m_pTempLine);

				//设置水平标注时竖直线
				m_pTempLineH1 = new QGraphicsLineItem;
				QPointF h1_begin(m_begin.x(), m_begin.y());
				QPointF h1_end(m_begin.x(), mouseEvent->scenePos().y() + 10);
				QLineF line1(h1_begin, h1_end);
				m_pTempLineH1->setLine(line1);
				m_pTempLineH1->setPen(pen);
				m_pDiagramScene->addItem(m_pTempLineH1);

				m_pTempLineH2 = new QGraphicsLineItem;
				QPointF h2_begin(m_end.x(), m_end.y());
				QPointF h2_end(m_end.x(), mouseEvent->scenePos().y() + 10);
				QLineF line2(h2_begin, h2_end);
				m_pTempLineH2->setPen(pen);
				m_pTempLineH2->setLine(line2);
				m_pDiagramScene->addItem(m_pTempLineH2);

				// 创建标注文本
				// 计算水平尺寸
				qreal horizontalDimension = std::abs(m_end.x() - m_begin.x());
				horizontalText = new QGraphicsTextItem(QString::number(horizontalDimension));
				horizontalText->setPos((m_begin.x() + m_end.x()) / 2, mouseEvent->scenePos().y() - 30);  // 文本位置可以根据需要调整
				m_pDiagramScene->addItem(horizontalText);
				
				break;

			}

			else if (m_dimDirection == DimVertical)
			{
				// 设置竖直标注线
				m_pTempLine = new QGraphicsLineItem;
				QPointF v_begin(mouseEvent->scenePos().x(), m_begin.y());
				QPointF v_end(mouseEvent->scenePos().x(), m_end.y());
				QLineF line(v_begin, v_end);

				QPen pen;
				pen.setColor(Qt::blue);
				m_pTempLine->setPen(pen);
				m_pTempLine->setLine(line);
				m_pDiagramScene->addItem(m_pTempLine);

				// 设置竖直标注时的水平线
				m_pTempLineV1 = new QGraphicsLineItem;
				QPointF v1_begin(m_begin.x(), m_begin.y());
				QPointF v1_end(mouseEvent->scenePos().x() + 10, m_begin.y());
				QLineF line1(v1_begin, v1_end);
				m_pTempLineV1->setLine(line1);
				m_pTempLineV1->setPen(pen);
				m_pDiagramScene->addItem(m_pTempLineV1);

				m_pTempLineV2 = new QGraphicsLineItem;
				QPointF v2_begin(m_end.x(), m_end.y());
				QPointF v2_end(mouseEvent->scenePos().x() + 10, m_end.y());
				QLineF line2(v2_begin, v2_end);
				m_pTempLineV2->setPen(pen);
				m_pTempLineV2->setLine(line2);
				m_pDiagramScene->addItem(m_pTempLineV2);

				// 创建标注文本并计算竖直尺寸
				qreal verticalDimension = std::abs(m_end.y() - m_begin.y());
				verticalText = new QGraphicsTextItem(QString::number(verticalDimension));
				verticalText->setPos(mouseEvent->scenePos().x() + 10, (m_begin.y() + m_end.y()) / 2);
				m_pDiagramScene->addItem(verticalText);
				break;

			}
			
		}
		
		case CREATEDIMENSION::DimRectangle:
			
		case CREATEDIMENSION::DimEllipse:// 若此前已经选中图形，且已获取了获取椭圆的起点和终点坐标
		{
			if (m_dimDirection == DimHorizontal)
			{
				// 设置水平标注线
				m_pTempLine = new QGraphicsLineItem;
				QPointF h_begin(m_begin.x(), mouseEvent->scenePos().y());
				QPointF h_end(m_end.x(), mouseEvent->scenePos().y());
				QLineF line(h_begin, h_end);
				// 创建一个 QPen 对象并设置颜色
				QPen pen;
				pen.setColor(Qt::blue);
				// 应用 QPen 到 QGraphicsLineItem
				m_pTempLine->setPen(pen);
				m_pTempLine->setLine(line);
				m_pDiagramScene->addItem(m_pTempLine);

				//设置水平标注时竖直线
				m_pTempLineH1 = new QGraphicsLineItem;
				QPointF h1_begin(m_begin.x(), (m_begin.y() + m_end.y()) / 2);
				QPointF h1_end(m_begin.x(), mouseEvent->scenePos().y() + 10);
				QLineF line1(h1_begin, h1_end);
				m_pTempLineH1->setLine(line1);
				m_pTempLineH1->setPen(pen);
				m_pDiagramScene->addItem(m_pTempLineH1);

				m_pTempLineH2 = new QGraphicsLineItem;
				QPointF h2_begin(m_end.x(), (m_begin.y() + m_end.y()) / 2);
				QPointF h2_end(m_end.x(), mouseEvent->scenePos().y() + 10);
				QLineF line2(h2_begin, h2_end);
				m_pTempLineH2->setPen(pen);
				m_pTempLineH2->setLine(line2);
				m_pDiagramScene->addItem(m_pTempLineH2);

				// 创建标注文本
				// 计算水平尺寸
				qreal horizontalDimension = std::abs(m_end.x() - m_begin.x());
				horizontalText = new QGraphicsTextItem(QString::number(horizontalDimension));
				horizontalText->setPos((m_begin.x() + m_end.x()) / 2, mouseEvent->scenePos().y() - 30);  // 文本位置可以根据需要调整
				m_pDiagramScene->addItem(horizontalText);
				break;
			}
			else if (m_dimDirection == DimVertical)
			{
				// 设置竖直标注线
				m_pTempLine = new QGraphicsLineItem;
				QPointF v_begin(mouseEvent->scenePos().x(), m_begin.y());
				QPointF v_end(mouseEvent->scenePos().x(), m_end.y());
				QLineF line(v_begin, v_end);
				// 创建一个 QPen 对象并设置颜色
				QPen pen;
				pen.setColor(Qt::blue);
				// 应用 QPen 到 QGraphicsLineItem
				m_pTempLine->setPen(pen);
				m_pTempLine->setLine(line);
				m_pDiagramScene->addItem(m_pTempLine);

				// 设置竖直标注时水平线
				m_pTempLineV1 = new QGraphicsLineItem;
				QPointF v1_begin((m_begin.x() + m_end.x()) / 2, m_begin.y());
				QPointF v1_end(mouseEvent->scenePos().x() + 10, m_begin.y());
				QLineF line1(v1_begin, v1_end);
				m_pTempLineV1->setLine(line1);
				m_pTempLineV1->setPen(pen);
				m_pDiagramScene->addItem(m_pTempLineV1);

				m_pTempLineV2 = new QGraphicsLineItem;
				QPointF v2_begin((m_begin.x() + m_end.x()) / 2, m_end.y());
				QPointF v2_end(mouseEvent->scenePos().x() + 10, m_end.y());
				QLineF line2(v2_begin, v2_end);
				m_pTempLineV2->setPen(pen);
				m_pTempLineV2->setLine(line2);
				m_pDiagramScene->addItem(m_pTempLineV2);

				// 创建标注文本
				// 计算竖直尺寸
				qreal verticalDimension = std::abs(m_end.y() - m_begin.y());
				verticalText = new QGraphicsTextItem(QString::number(verticalDimension));
				verticalText->setPos(mouseEvent->scenePos().x() + 10, (m_begin.y() + m_end.y()) / 2);  // 文本位置可以根据需要调整
				m_pDiagramScene->addItem(verticalText);
				break;
			}
		   
		}
		default:
			break;
		}
		
		Prompt(QStringLiteral("单击鼠标左键完成标注"));
		break;
	}
	case 2:
	{
		m_nStep = 0;
		break;
	}
	default:
		break;
	}
	return 0;
}


int	CREATEDIMENSION::OnMouseMove(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_pSelItem == NULL)
	{
		return CCommand::OnMouseMove(mouseEvent);
	}

	switch (m_nStep)
	{
	case 0:
	{
		Prompt(QStringLiteral("单击鼠标左键开始标注"));
		break;
	}
	case 1:
	{
		Prompt(QStringLiteral("单击鼠标左键完成标注"));
		switch (dimType)
		{
		case CREATEDIMENSION::DimNull:
			break;
		case CREATEDIMENSION::DimLine:
		{	
			if (m_dimDirection == DimHorizontal)
			{
			// 更新水平标注线
			QPointF h_begin(m_begin.x(), mouseEvent->scenePos().y());
			QPointF h_end(m_end.x(), mouseEvent->scenePos().y());
			QLineF line(h_begin, h_end);
			m_pTempLine->setLine(line);
			//设置水平标注时竖直线

			QPointF h1_begin(m_begin.x(), m_begin.y());
			QPointF h1_end(m_begin.x(), mouseEvent->scenePos().y() + 10);
			QLineF line1(h1_begin, h1_end);
			m_pTempLineH1->setLine(line1);

			QPointF h2_begin(m_end.x(), m_end.y());
			QPointF h2_end(m_end.x(), mouseEvent->scenePos().y() + 10);
			QLineF line2(h2_begin, h2_end);
			m_pTempLineH2->setLine(line2);

			horizontalText->setPos((m_begin.x() + m_end.x()) / 2, mouseEvent->scenePos().y() - 30);  // 文本位置可以根据需要调整
			
			if (!leftArrow) {
				QPolygonF arrowHead; // 定义箭头形状
				arrowHead << QPoint(0, 0) << QPoint(-10, 5) << QPoint(-10, -5); // 箭头的大小和形状

				// 左端箭头
				leftArrow = new QGraphicsPolygonItem(arrowHead);
				leftArrow->setBrush(QBrush(Qt::black));
				leftArrow->setPen(QPen(Qt::black));
				leftArrow->setRotation(180); // 初始角度旋转

				// 右端箭头
				rightArrow = new QGraphicsPolygonItem(arrowHead);
				rightArrow->setBrush(QBrush(Qt::black));
				rightArrow->setPen(QPen(Qt::black));

				// 添加到场景中
				m_pDiagramScene->addItem(leftArrow);
				m_pDiagramScene->addItem(rightArrow);
			}

			// 更新箭头位置
			leftArrow->setPos(h_begin.x(), h_begin.y()); // 更新左箭头位置
			rightArrow->setPos(h_end.x(), h_end.y());    // 更新右箭头位置

			break;
			}
			
			else if (m_dimDirection == DimVertical)
			{
				// 更新竖直标注线
				QPointF v_begin(mouseEvent->scenePos().x(), m_begin.y());
				QPointF v_end(mouseEvent->scenePos().x(), m_end.y());
				QLineF line(v_begin, v_end);
				m_pTempLine->setLine(line);

				// 设置竖直标注时的水平线
				QPointF v1_begin(m_begin.x(), m_begin.y());
				QPointF v1_end(mouseEvent->scenePos().x() + 10, m_begin.y());
				QLineF line1(v1_begin, v1_end);
				m_pTempLineV1->setLine(line1);

				QPointF v2_begin(m_end.x(), m_end.y());
				QPointF v2_end(mouseEvent->scenePos().x() + 10, m_end.y());
				QLineF line2(v2_begin, v2_end);
				m_pTempLineV2->setLine(line2);

				// 更新竖直标注文本位置
				verticalText->setPos(mouseEvent->scenePos().x() + 10, (m_begin.y() + m_end.y()) / 2); // 文本位置可以根据需要调整
				
				if (!topArrow) {
					QPolygonF arrowHead; // 定义箭头形状
					arrowHead << QPoint(0, 0) << QPoint(-10, 5) << QPoint(-10, -5); // 箭头的大小和形状

					// 顶端箭头
					topArrow = new QGraphicsPolygonItem(arrowHead);
					topArrow->setBrush(QBrush(Qt::black));
					topArrow->setPen(QPen(Qt::black));
					topArrow->setRotation(-90); // 顶部箭头

					// 底端箭头
					bottomArrow = new QGraphicsPolygonItem(arrowHead);
					bottomArrow->setBrush(QBrush(Qt::black));
					bottomArrow->setPen(QPen(Qt::black));
					bottomArrow->setRotation(90); // 底部箭头

					// 添加到场景中
					m_pDiagramScene->addItem(topArrow);
					m_pDiagramScene->addItem(bottomArrow);
				}

				topArrow->setPos(v_begin.x(), v_begin.y());    // 更新顶部箭头位置
				bottomArrow->setPos(v_end.x(), v_end.y());     // 更新底部箭头位置

				break;
			}
			
		}
		case CREATEDIMENSION::DimRectangle:
			
		case CREATEDIMENSION::DimEllipse:
		{
			if (m_dimDirection == DimHorizontal)
			{
				// 更新水平标注线
				QPointF h_begin(m_begin.x(), mouseEvent->scenePos().y());
				QPointF h_end(m_end.x(), mouseEvent->scenePos().y());
				QLineF line(h_begin, h_end);
				m_pTempLine->setLine(line);

				//设置水平标注时竖直线
				QPointF h1_begin(m_begin.x(), (m_begin.y() + m_end.y()) / 2);
				QPointF h1_end(m_begin.x(), mouseEvent->scenePos().y() + 10);
				QLineF line1(h1_begin, h1_end);
				m_pTempLineH1->setLine(line1);

				QPointF h2_begin(m_end.x(), (m_begin.y() + m_end.y()) / 2);
				QPointF h2_end(m_end.x(), mouseEvent->scenePos().y() + 10);
				QLineF line2(h2_begin, h2_end);
				m_pTempLineH2->setLine(line2);

				horizontalText->setPos((m_begin.x() + m_end.x()) / 2, mouseEvent->scenePos().y() - 30);  // 文本位置可以根据需要调整
				
				if (!leftArrow) {
					QPolygonF arrowHead; // 定义箭头形状
					arrowHead << QPoint(0, 0) << QPoint(-10, 5) << QPoint(-10, -5); // 箭头的大小和形状

					// 左端箭头
					leftArrow = new QGraphicsPolygonItem(arrowHead);
					leftArrow->setBrush(QBrush(Qt::black));
					leftArrow->setPen(QPen(Qt::black));
					leftArrow->setRotation(180); // 初始角度旋转

					// 右端箭头
					rightArrow = new QGraphicsPolygonItem(arrowHead);
					rightArrow->setBrush(QBrush(Qt::black));
					rightArrow->setPen(QPen(Qt::black));

					// 添加到场景中
					m_pDiagramScene->addItem(leftArrow);
					m_pDiagramScene->addItem(rightArrow);
				}

				// 更新箭头位置
				leftArrow->setPos(h_begin.x(), h_begin.y()); // 更新左箭头位置
				rightArrow->setPos(h_end.x(), h_end.y());    // 更新右箭头位置
				
				break;
			}

			else if (m_dimDirection == DimVertical)
			{
				// 更新竖直标注线
				QPointF v_begin(mouseEvent->scenePos().x(), m_begin.y());
				QPointF v_end(mouseEvent->scenePos().x(), m_end.y());
				QLineF line(v_begin, v_end);
				m_pTempLine->setLine(line);

				// 设置竖直标注时的水平线
				QPointF v1_begin((m_begin.x() + m_end.x()) / 2, m_begin.y());
				QPointF v1_end(mouseEvent->scenePos().x() + 10, m_begin.y());
				QLineF line1(v1_begin, v1_end);
				m_pTempLineV1->setLine(line1);

				QPointF v2_begin((m_begin.x() + m_end.x()) / 2, m_end.y());
				QPointF v2_end(mouseEvent->scenePos().x() + 10, m_end.y());
				QLineF line2(v2_begin, v2_end);
				m_pTempLineV2->setLine(line2);

				// 更新竖直标注文本位置
				verticalText->setPos(mouseEvent->scenePos().x() + 10, (m_begin.y() + m_end.y()) / 2);  // 文本位置可以根据需要调整
				
				if (!topArrow) {
					QPolygonF arrowHead; // 定义箭头形状
					arrowHead << QPoint(0, 0) << QPoint(-10, 5) << QPoint(-10, -5); // 箭头的大小和形状

					// 顶端箭头
					topArrow = new QGraphicsPolygonItem(arrowHead);
					topArrow->setBrush(QBrush(Qt::black));
					topArrow->setPen(QPen(Qt::black));
					topArrow->setRotation(-90); // 顶部箭头

					// 底端箭头
					bottomArrow = new QGraphicsPolygonItem(arrowHead);
					bottomArrow->setBrush(QBrush(Qt::black));
					bottomArrow->setPen(QPen(Qt::black));
					bottomArrow->setRotation(90); // 底部箭头

					// 添加到场景中
					m_pDiagramScene->addItem(topArrow);
					m_pDiagramScene->addItem(bottomArrow);
				}

				topArrow->setPos(v_begin.x(), v_begin.y());    // 更新顶部箭头位置
				bottomArrow->setPos(v_end.x(), v_end.y());     // 更新底部箭头位置
				
				break;
			}
			
		}
			
		default:
			break;
		}

	}
	default:
		break;
	}

	return 0;
}

// 单击鼠标右键取消当前的操作
int	CREATEDIMENSION::OnRButtonDown(QGraphicsSceneMouseEvent* mouseEvent)
{
	
	return 0;
}
// 调用Cancel 函数取消本次操作
int CREATEDIMENSION::Cancel()
{
	if (m_nStep == 1) {
		;
	}

	m_nStep = 0; // 将操作步重置为 0 
	Prompt(QStringLiteral("就绪")); // 等待提示新类型的命令操作
	return 0;
}

//绘制水平尺寸标注
int CREATEDIMENSION::DrawHorizontalDimension(const QPointF& start, const QPointF& end)
{
	// 计算水平尺寸
	qreal horizontalDimension = std::abs(end.x() - start.x());

	// 创建水平尺寸线
	QGraphicsLineItem* horizontalLine = new QGraphicsLineItem(QLineF(start.x(), start.y(), end.x(), start.y()));
	m_pDiagramScene->addItem(horizontalLine);

	// 创建标注文本
	QGraphicsTextItem* horizontalText = new QGraphicsTextItem(QString::number(horizontalDimension));
	horizontalText->setPos((start.x() + end.x()) / 2, start.y() - 10);  // 文本位置可以根据需要调整
	m_pDiagramScene->addItem(horizontalText);

	return 0;
}


//绘制竖直尺寸标注
int CREATEDIMENSION::DrawVerticalDimension(const QPointF& start, const QPointF& end)
{
	// 计算竖直尺寸
	qreal verticalDimension = std::abs(end.y() - start.y());

	// 创建竖直尺寸线
	QGraphicsLineItem* verticalLine = new QGraphicsLineItem(QLineF(start.y(), start.x(), end.y(), start.x()));
	m_pDiagramScene->addItem(verticalLine);

	// 创建标注文本
	QGraphicsTextItem* verticalText = new QGraphicsTextItem(QString::number(verticalDimension));
	verticalText->setPos((start.y() + end.y()) / 2, start.x() - 10);  // 文本位置可以根据需要调整
	m_pDiagramScene->addItem(verticalText);

	return 0;
}

