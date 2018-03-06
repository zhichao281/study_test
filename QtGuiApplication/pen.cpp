#include "pen.h"

#include <QDebug>
Pen::Pen()
{
	;
}

void Pen::paint(QPainter &paint)
{
	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);
	paint.setRenderHint(QPainter::Antialiasing, true);// ��ֱֹ������
	paint.drawLine(m_startPoint, m_endPoint);
	qDebug() << "start:" << m_startPoint;
}

int Pen::get_DrawType()
{
	return 3;
}