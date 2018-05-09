#include "DrawArrow.h"

#include <QPainter>

CDrawArrow::CDrawArrow()
{
}



void CDrawArrow::paintDrawItem(QPainter &paint)
{
	double par = 15.0;//箭头部分三角形的腰长
	double slopy = atan2((m_endPoint.y() - m_startPoint.y()), (m_endPoint.x() - m_startPoint.x()));
	double cosy = cos(slopy);
	double siny = sin(slopy);
	QPoint point1 = QPoint(m_endPoint.x() + int(-par * cosy - (par / 2.0*siny)), m_endPoint.y() + int(-par * siny + (par / 2.0*cosy)));
	QPoint point2 = QPoint(m_endPoint.x() + int(-par * cosy + (par / 2.0*siny)), m_endPoint.y() - int(par / 2.0*cosy + par * siny));
	QPoint points[3] = { m_endPoint, point1, point2 };

	QPen drawTrianglePen;//创建画笔
	drawTrianglePen.setColor(QColor(255,0,0));
	drawTrianglePen.setWidth(1);
	paint.setPen(drawTrianglePen);
	paint.setBrush(QColor(255,0,0));

	paint.drawPolygon(points, 3);//绘制箭头部分
	int offsetX = int(par*siny / 3);
	int offsetY = int(par*cosy / 3);
	QPoint point3, point4;
	point3 = QPoint(m_endPoint.x() + int(-par * cosy - (par / 2.0*siny)) + offsetX, m_endPoint.y() + int(-par * siny + (par / 2.0*cosy)) - offsetY);
	point4 = QPoint(m_endPoint.x() + int(-par * cosy + (par / 2.0*siny) - offsetX), m_endPoint.y() - int(par / 2.0*cosy + par * siny) + offsetY);
	QPoint arrowBodyPoints[3] = { m_startPoint, point3, point4 };
	paint.drawPolygon(arrowBodyPoints, 3);//绘制箭身部分

}

int CDrawArrow::getDrawType()
{
	return DRAW_TYPE::Draw_Arrow;
}