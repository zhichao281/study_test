#include "DrawPolygon.h"


CDrawPolygon::CDrawPolygon()
{

}

void CDrawPolygon::paintDrawItem(QPainter &paint)
{
	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);
	QPolygon polygon(m_vecPolygonStack.size());
	for (auto i = 0 ; i < m_vecPolygonStack.size(); ++i)
	{
		polygon.setPoint(i, *m_vecPolygonStack[i]);
	}
	paint.setRenderHint(QPainter::Antialiasing, true);// 防止直线走样
	paint.drawPolygon(polygon);
}

int CDrawPolygon::getDrawType()
{
	return DRAW_TYPE::Draw_Polygon;
}

void CDrawPolygon::addPoint(QPoint *p)
{
	m_vecPolygonStack.push_back(p);
}

QPoint *CDrawPolygon::getLastPoint()
{
	return m_vecPolygonStack[m_vecPolygonStack.size() - 1];
}

CDrawPolygon::~CDrawPolygon()
{
	foreach(QPoint *p, m_vecPolygonStack)
	{
		delete p;
		p = nullptr;
	}
}

int CDrawPolygon::get_size()
{
	return m_vecPolygonStack.size();
}

QPoint* CDrawPolygon::index(int nPointIndex)
{
	return m_vecPolygonStack[nPointIndex];
}