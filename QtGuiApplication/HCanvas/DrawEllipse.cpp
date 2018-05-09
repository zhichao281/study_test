#include "DrawEllipse.h"


CDrawEllipse::CDrawEllipse()
{

}

void CDrawEllipse::paintDrawItem(QPainter &paint)
{
	paint.setPen(QPen(m_penColor, m_nPenSize));
	paint.setBrush(m_brushColor);
	paint.drawEllipse(m_startPoint, m_endPoint.rx() - m_startPoint.rx(), m_endPoint.ry() - m_startPoint.ry());
}

int CDrawEllipse::getDrawType()
{
	return DRAW_TYPE::Draw_Ellipse;
}