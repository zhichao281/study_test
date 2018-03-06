#include "BkImageWidget.h"

CBkImageWidget::CBkImageWidget(QWidget *parent)
	: QWidget(parent)
{

	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setMouseTracking(true);

	setAutoFillBackground(true);
}

CBkImageWidget::~CBkImageWidget()
{

}



/**
* @brief …Ë÷√±≥æ∞Õº∆¨
* @param strFile   Õº∆¨¬∑æ∂
* @return
*/
bool CBkImageWidget::SetBkImage(QString strFile)
{
	QPalette palette;
	QPixmap pixmap(strFile);
	palette.setBrush(QPalette::Window, QBrush(pixmap));
	setPalette(palette);
	return true;
}
