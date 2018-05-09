#include "DrawText.h"

#include <QDebug>

CDrawText::CDrawText()
{
	


}


CDrawText::~CDrawText()
{


}
void CDrawText::paintDrawItem(QPainter &painter)
{
	if (m_strText.size()<1)
	{
		return;
	}

	painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
	//painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
	// ���û�����ɫ
	painter.setPen(QColor(255,0,0));

	QFont font;
	font.setFamily("Microsoft YaHei");
	// ��С
	font.setPointSize(12);

	// ʹ������
	painter.setFont(font);
	
	// �����ı�
	QTextOption option(Qt::AlignJustify);
	option.setWrapMode(QTextOption::WordWrap);
	painter.drawText(m_rect, Qt::TextWrapAnywhere, m_strText);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

}

int CDrawText::getDrawType()
{
	return DRAW_TYPE::Draw_Text;
}

void CDrawText::startDraw(QGraphicsSceneMouseEvent * event)
{
}

void CDrawText::drawing(QGraphicsSceneMouseEvent * event)
{
}
