#include "DrawRect.h"

#include <QGraphicsRectItem>
CDrawRect::CDrawRect()
{

}

void CDrawRect::paintDrawItem(QPainter &paint)
{
	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.drawRect(m_startPoint.x(), m_startPoint.y(), m_endPoint.x() - m_startPoint.x(), m_endPoint.y() - m_startPoint.y());
}

int CDrawRect::getDrawType()
{
	return DRAW_TYPE::Draw_Rect;
}
void CDrawRect::startDraw(QGraphicsSceneMouseEvent * event)
{
	setRect(QRectF(event->scenePos(), QSizeF(0, 0)));
}

void CDrawRect::drawing(QGraphicsSceneMouseEvent * event)
{
	QRectF r(rect().topLeft(),
		QSizeF(event->scenePos().x() - rect().topLeft().x(), event->scenePos().y() - rect().topLeft().y()));
	setRect(r);
}
