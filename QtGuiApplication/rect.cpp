#include "rect.h"


Rect::Rect()
{

}

void Rect::paint(QPainter &paint)
{
	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);
	paint.setRenderHint(QPainter::Antialiasing, true);// 防止直线走样
	paint.drawRect(m_startPoint.x(), m_startPoint.y(), m_endPoint.x() - m_startPoint.x(), m_endPoint.y() - m_startPoint.y());
}

int Rect::get_DrawType()
{
	return 1;
}