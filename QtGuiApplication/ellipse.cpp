#include "ellipse.h"


Ellipse::Ellipse()
{

}

void Ellipse::paint(QPainter &paint)
{
	paint.setPen(QPen(m_penColor, m_nPenSize));
	paint.setBrush(m_brushColor);
	paint.drawEllipse(m_startPoint, m_endPoint.rx() - m_startPoint.rx(), m_endPoint.ry() - m_startPoint.ry());
}

int Ellipse::get_DrawType()
{
	return DRAW_TYPE::Draw_Ellipse;
}