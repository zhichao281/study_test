#include "CErase.h"



CErase::CErase()
{
}



void CErase::paint(QPainter &paint)
{
	QRect rect = QRect(QPoint(m_endPoint.x() - m_nPenSize/2, m_endPoint.y() - m_nPenSize/2), QPoint(m_endPoint.x() + m_nPenSize/2, m_endPoint.y() + m_nPenSize/2));  //ÏðÆ¤²Á´óÐ¡
	paint.eraseRect(rect);
}

int CErase::get_DrawType()
{
	return DRAW_TYPE::Draw_Erase;
}