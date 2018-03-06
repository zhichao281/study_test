#include "BaseShape.h"  
#include <QDebug>
CBaseShape::CBaseShape()
	:m_startPoint(QPoint(0, 0)), m_endPoint(QPoint(0, 0))
{
	m_PenCapstyle= Qt::RoundCap;
}

void CBaseShape::set_end(QPoint p)
{
	m_endPoint = p;
}

void CBaseShape::set_start(QPoint p)
{
	m_startPoint = p;
}
void CBaseShape::setCapStyle(Qt::PenCapStyle pcs)
{
	m_PenCapstyle = pcs;

}

void CBaseShape::set_pos(QPoint p1, QPoint p2, bool is_straight)
{
	m_startPoint = p1;
	int dis;
	if (is_straight)
	{
		if (abs(p1.rx() - p2.rx()) < abs(p1.ry() - p2.ry()))
			dis = abs(p1.rx() - p2.rx());
		else
			dis = abs(p1.ry() - p2.ry());
		if (p1.rx() - p2.rx() > 0)
			p2.setX(p1.rx() - dis);
		else
			p2.setX(p1.rx() + dis);

		if (p1.ry() - p2.ry() > 0)
			p2.setY(p1.ry() - dis);
		else
			p2.setY(p1.ry() + dis);
	}
	m_endPoint = p2;
}

QPoint CBaseShape::get_end()
{
	return m_endPoint;
}

QPoint CBaseShape::get_start()
{
	return m_startPoint;
}
int CBaseShape::showShape(QPoint point)
{
	return 0;

}
void CBaseShape::setDrawType(int nDrawType)
{
	m_nDrawType = nDrawType;

}

QColor CBaseShape::get_color()
{
	return m_penColor;
}

QColor CBaseShape::get_brush()
{
	return  m_brushColor;
}

int CBaseShape::get_width()
{
	return m_nPenSize;
}

void CBaseShape::Set_Parent(QWidget *parent)
{
	return;

}

void CBaseShape::set(QColor c1, QColor c2, int w)
{
	m_penColor = c1;
	m_brushColor = c2;
	m_nPenSize = w;
}