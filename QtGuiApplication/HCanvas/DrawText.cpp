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
	// 设置画笔颜色
	painter.setPen(QColor(255,0,0));

	QFont font;
	font.setFamily("Microsoft YaHei");
	// 大小
	font.setPointSize(12);

	// 使用字体
	painter.setFont(font);
	
	// 绘制文本
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
