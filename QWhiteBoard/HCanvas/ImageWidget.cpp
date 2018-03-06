#include "ImageWidget.h"

#include <QPainter>

/**********插入图片********************/

ImageWidget::ImageWidget(QWidget *parent)
: QWidget(parent)
{

	m_Angle = 0;
	bFit = true;
	m_bEditState = true;
	m_nMargin = 20;
	m_nShadow_Width = 10;
	setMouseTracking(true);
	setWindowFlags(Qt::FramelessWindowHint);//无边框
	m_bleftPressed = false;
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	_curpos = 0;//标记鼠标左击时的位置

	m_nMarginWidth = 6;

}

ImageWidget::~ImageWidget()
{

}

void ImageWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPixmap pixmap = m_pixmap;
	if (m_Angle)
	{

		QMatrix leftmatrix;
		leftmatrix.rotate(m_Angle);
		pixmap = m_pixmap.transformed(leftmatrix, Qt::SmoothTransformation);

	}

	if (m_bEditState)
	{

		pixmap = pixmap.scaled(width() - m_nMarginWidth, height() - m_nMarginWidth, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		painter.drawPixmap(m_nMarginWidth / 2, m_nMarginWidth / 2, pixmap);


		int nWidth = this->width();
		int nHeight = this->height();
		int rectWidth = 6;
		int rectHeight = 6;

		QPen pen;  // creates a default pen
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(1);
		pen.setBrush(Qt::blue);
		pen.setCapStyle(Qt::RoundCap);
		pen.setJoinStyle(Qt::RoundJoin);
		painter.setPen(pen);
		QRectF rectangle1;
		rectangle1.setRect(m_nMarginWidth / 2, m_nMarginWidth / 2, nWidth - m_nMarginWidth, nHeight - m_nMarginWidth);
		painter.drawRect(rectangle1);


		//painter.drawLine(10,5,220,220);

		painter.setPen(Qt::blue);
		painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
		QRectF rectangle2(0, 0, rectWidth, rectHeight);
		painter.drawRect(rectangle2);
		rectangle2.setRect(0, nHeight / 2, rectWidth, rectHeight);
		painter.drawRect(rectangle2);
		rectangle2.setRect(0, nHeight - rectHeight - 1, rectWidth, rectHeight);
		painter.drawRect(rectangle2);
		rectangle2.setRect(nWidth / 2, 0, rectWidth, rectHeight);

		painter.drawRect(rectangle2);
		rectangle2.setRect(nWidth / 2, nHeight - rectHeight - 1, rectWidth, rectHeight);

		painter.drawRect(rectangle2);
		rectangle2.setRect(nWidth - rectWidth - 1, 0, rectWidth, rectHeight);
		painter.drawRect(rectangle2);
		rectangle2.setRect(nWidth - rectWidth - 1, nHeight / 2, rectWidth, rectHeight);
		painter.drawRect(rectangle2);
		rectangle2.setRect(nWidth - rectWidth - 1, nHeight - rectHeight - 1, rectWidth, rectHeight);
		painter.drawRect(rectangle2);

	}
	else
	{
		pixmap = pixmap.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		painter.drawPixmap(0, 0, pixmap);
	}




}

void ImageWidget::setPixmap(QString fileName)
{
	m_pixmap.load(fileName);
	update();
}

void ImageWidget::setPixmap(QPixmap pix)
{
	m_pixmap = pix;
	update();
}

void ImageWidget::setSize(int nWidth, int nHeight)
{
	this->setGeometry(this->pos().x(), this->pos().y(), nWidth + m_nMarginWidth, nHeight + m_nMarginWidth);

}

QPixmap ImageWidget::getPixmap()
{
	return m_pixmap;
}

void ImageWidget::SetImageInfo(int nPenid)
{
	m_nPenid = nPenid;
}

int ImageWidget::GetImageInfo(int &nPenid)
{
	nPenid = m_nPenid;

	return m_nPenid;

}

/**
* @brief 旋转图片
*/
void ImageWidget::RotateImage(qreal angle)
{
	m_Angle += angle;
	if (m_Angle == 360)
		m_Angle = 0;
	int nWidth = this->width();
	int nHeight = this->height();
	this->setGeometry(this->pos().x() + nWidth / 2.0 - nHeight / 2.0, this->pos().y() - nWidth / 2.0 + nHeight / 2.0, nHeight, nWidth);
	update();

}



qreal ImageWidget::GetRotate()
{
	return m_Angle;
}


/**
* @brief 鼠标移动事件
*/
void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	if ((x - oldX)>0)
		rolatetY++;
	if (rolatetY == 360){ rolatetY = 0; }
	if (y - oldY > 0)
		rolatetX++;
	if (rolatetX == 360){ rolatetX = 0; }


	int nPoint = countFlag(event->pos(), countRow(event->pos()));
	setCursorType(nPoint);
	if (m_bleftPressed)//是否左击
	{
		QPoint ptemp = event->globalPos();
		ptemp = ptemp - m_endPnt;
		if (_curpos == 22)//移动窗口
		{
			ptemp = ptemp + pos();
			move(ptemp);
		}
		else
		{
			QRect wid = geometry();
			switch (_curpos)//改变窗口的大小
			{

			case 11:wid.setTopLeft(wid.topLeft() + ptemp); break;//左上角
			case 13:wid.setTopRight(wid.topRight() + ptemp); break;//右上角
			case 31:wid.setBottomLeft(wid.bottomLeft() + ptemp); break;//左下角
			case 33:wid.setBottomRight(wid.bottomRight() + ptemp); break;//右下角
			case 12:wid.setTop(wid.top() + ptemp.y()); break;//中上角
			case 21:wid.setLeft(wid.left() + ptemp.x()); break;//中左角
			case 23:wid.setRight(wid.right() + ptemp.x()); break;//中右角
			case 32:wid.setBottom(wid.bottom() + ptemp.y()); break;//中下角
			}
			setGeometry(wid);
		}

		m_endPnt = event->globalPos();//更新位置
	}
	event->ignore();
	update();

}

/**
* @brief 鼠标按下事件
*/
void ImageWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		this->m_bleftPressed = true;

		QPoint temp = event->globalPos();
		m_endPnt = temp;
		_curpos = countFlag(event->pos(), countRow(event->pos()));
		oldY = event->pos().y();
		oldX = event->pos().x();
		event->ignore();

	}
	QWidget::mousePressEvent(event);
}

/**
* @brief 鼠标释放事件
*/
void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_bleftPressed)
		m_bleftPressed = false;
	setCursor(Qt::ArrowCursor);
	event->ignore();
}

/**
* @brief 计算鼠标在哪一列和哪一行
* @param p        坐标点
* @param row      在哪一列位置
*/
int ImageWidget::countFlag(QPoint p, int row)//
{
	if (p.y()<m_nMargin)
		return 10 + row;
	else if (p.y()>this->height() - m_nMargin)
		return 30 + row;
	else
		return 20 + row;
}

/**
* @brief 根据鼠标所在位置改变鼠标指针形状
* @param flag        位置
*/
void ImageWidget::setCursorType(int flag)//
{
	Qt::CursorShape cursor;
	switch (flag)
	{
	case 11:
	case 33:
	{
			   cursor = Qt::SizeFDiagCursor;
			   break;
	}
	case 13:
	case 31:
	{
			   cursor = Qt::SizeBDiagCursor;
			   break;
	}
	case 21:
	case 23:
	{
			   cursor = Qt::SizeHorCursor;
			   break;
	}
	case 12:
	case 32:
	{
			   cursor = Qt::SizeVerCursor;
			   break;
	}
	case 22:
	{
			   if (m_bleftPressed)
				   cursor = Qt::ClosedHandCursor;
			   else
				   cursor = Qt::OpenHandCursor;
			   break;
	}
	default:
	{
			   cursor = Qt::ArrowCursor;
			   break;
	}
	}
	setCursor(cursor);
}
//计算在哪一列
int ImageWidget::countRow(QPoint p)
{
	return (p.x()<m_nMargin) ? 1 : (p.x()>(this->width() - m_nMargin) ? 3 : 2);
}

void ImageWidget::SetEditState(bool bState)
{

	int nWidth = this->width();
	int nHeight = this->height();
	if (m_bEditState == true && bState == false)
	{
		this->setGeometry(this->pos().x() + m_nMarginWidth / 2, this->pos().y() + m_nMarginWidth / 2, nWidth - m_nMarginWidth, nHeight - m_nMarginWidth);

	}
	if (m_bEditState == false && bState == true)
	{
		this->setGeometry(this->pos().x() - m_nMarginWidth / 2, this->pos().y() - m_nMarginWidth / 2, nWidth + m_nMarginWidth, nHeight + m_nMarginWidth);
	}

	m_bEditState = bState;
	update();
}
