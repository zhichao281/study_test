#include "Polygon.h"


Polygon::Polygon()
{

}

void Polygon::paint(QPainter &paint)
{
	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);
	QPolygon polygon(polygonStack.size());
	for (int i = 0; i < polygonStack.size(); ++i)
	{
		polygon.setPoint(i, *polygonStack[i]);
	}
	paint.setRenderHint(QPainter::Antialiasing, true);// 防止直线走样
	paint.drawPolygon(polygon);
}

int Polygon::get_DrawType()
{
	return 5;
}

void Polygon::push(QPoint *p)
{
	polygonStack.push_back(p);
}

QPoint *Polygon::top()
{
	return polygonStack[polygonStack.size() - 1];
}

Polygon::~Polygon()
{
	foreach(QPoint *p, polygonStack)
	{
		delete p;
	}
}

int Polygon::get_size()
{
	return polygonStack.size();
}

QPoint* Polygon::index(int pos)
{
	return polygonStack[pos];
}