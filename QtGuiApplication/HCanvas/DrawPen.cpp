#include "DrawPen.h"

#include <QDebug>
CDrawPen::CDrawPen()
{
	
}

void CDrawPen::paintDrawItem(QPainter &paint)
{
	clock_t start_time = clock();

	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);

	//for (int i = 0; i < m_vecPonitStack.size() - 1; i++)
	//{
	//	paint.drawLine(m_vecPonitStack[i].x(), m_vecPonitStack[i].y(), m_vecPonitStack[i + 1].x(), m_vecPonitStack[i + 1].y());  //遍历所有点来画线
	//}

	if (m_vecPonitStack.size() == 1)
	{
		paint.drawLine(m_startPoint, m_endPoint);
	}
	else
	{
		paint.drawPolyline(m_vecPonitStack);
	}

	clock_t end_time = clock();
	qDebug() << "size:" << m_vecPonitStack.size() << " ; time" << end_time - start_time ;
}

int CDrawPen::getDrawType()
{
	return DRAW_TYPE::Draw_Pen;
}

void CDrawPen::addPoint(QPoint point)
{
	//忽略跟上一个点相同的点
	QVector<QPoint> vectPos = m_vecPonitStack;
	if (!vectPos.isEmpty())
	{
		if (vectPos.last() == point)
			return;
	}

	m_vecPonitStack.push_back(point);
}

void CDrawPen::startDraw(QGraphicsSceneMouseEvent * event)
{
}

void CDrawPen::drawing(QGraphicsSceneMouseEvent * event)
{
}
