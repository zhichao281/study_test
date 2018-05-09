#include "DrawLine.h"


CDrawLine::CDrawLine()
{

}

void CDrawLine::paintDrawItem(QPainter &paint)
{
	QPen pen(m_penColor, m_nPenSize);

	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);
	paint.drawLine(m_startPoint, m_endPoint);
}

int CDrawLine::getDrawType()
{
	return DRAW_TYPE::Draw_Line;
}
void CDrawLine::startDraw(QGraphicsSceneMouseEvent * event)
{
	setLine(QLineF(event->scenePos(), event->scenePos()));
}

void CDrawLine::drawing(QGraphicsSceneMouseEvent * event)
{
	QLineF newLine(line().p1(), event->scenePos());
	setLine(newLine);
}
