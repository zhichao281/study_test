#include "line.h"


Line::Line()
{

}

void Line::paint(QPainter &paint)
{
	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);
	paint.setRenderHint(QPainter::Antialiasing, true);// ��ֱֹ������
	paint.drawLine(m_startPoint, m_endPoint);
}

int Line::get_DrawType()
{
	return 2;
}