#include "DrawImage.h"


#include <QDebug>
CDrawImage::CDrawImage()
{
}


CDrawImage::~CDrawImage()
{
}

void CDrawImage::paintDrawItem(QPainter &painter, int nWidth, int nHeight)
{
	painter.drawPixmap(m_rect, m_pixmap);

}

int CDrawImage::getDrawType()
{
	return DRAW_TYPE::Draw_Image;
}