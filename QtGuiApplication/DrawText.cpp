#include "DrawText.h"

#include <QDebug>

CDrawText::CDrawText()
{
	bFocus = false;
	this->setWindowFlags(Qt::FramelessWindowHint);

}


CDrawText::~CDrawText()
{


}
void CDrawText::paint(QPainter &paint)
{
	if (bFocus == true)
	{
		return;
	}
	QPen pen(m_penColor, m_nPenSize);
	pen.setCapStyle(m_PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	paint.setPen(pen);
	paint.setBrush(m_brushColor);
	paint.setRenderHint(QPainter::Antialiasing, true);// 防止直线走样
	paint.drawText(m_startPoint.x()+2, m_startPoint.y()+this->height()/2+2, this->text());
}

int CDrawText::get_DrawType()
{
	return Draw_Text;
}

void CDrawText::Set_Parent(QWidget *parent)
{
	this->setParent(parent);
	return;

}
int CDrawText::showShape(QPoint point)
{
	if (bFocus == false)
	{
		this->move(point);//你喜欢的位置。
		this->show();
	}
	qDebug() << "m_startPoint" << point;
	return 0;
}
void CDrawText::focusInEvent(QFocusEvent *e)
{

	bFocus = true;
	QPalette p = QPalette();
	p.setColor(QPalette::Base, Qt::green);    //QPalette::Base 对可编辑输入框有效，还有其他类型，具体的查看文档
	setPalette(p);


	return;
}

void CDrawText::focusOutEvent(QFocusEvent *e)
{
	bFocus = false;
	QPalette p1 = QPalette();
	p1.setColor(QPalette::Base, Qt::white);
	setPalette(p1);
	this->close();
}