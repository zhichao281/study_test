
#include "BaseShape.h"  

#include <QDebug>
//构造函数
CBaseShape::CBaseShape()
	:m_startPoint(QPoint(0, 0)), m_endPoint(QPoint(0, 0))
{
	m_PenCapstyle= Qt::RoundCap;
}

//析构函数
CBaseShape::~CBaseShape()
{

}

//设置图形的起始点
void CBaseShape::setStartPoint(QPoint startPoint)
{
	m_startPoint = startPoint;
}

//设置图形的结束点
void CBaseShape::setEndPoint(QPoint endPoint)
{
	m_endPoint = endPoint;
}

//设置绘制坐标信息
void CBaseShape::setDrawPoint(QPoint startPoint, QPoint endPoint, bool bStraight)
{
	m_startPoint = startPoint;
	int nDistance; //相对位移
	
	if (bStraight )
	{
		//如果是直线就强制为水平或者垂直
		if (getDrawType() == DRAW_TYPE::Draw_Line)
		{
			//判断x,y轴的相对位移，取最大值
			if (abs(startPoint.rx() - endPoint.rx()) < abs(startPoint.ry() - endPoint.ry()))	
			{
				endPoint.setX(startPoint.rx());
			}
			else
			{
				endPoint.setY(startPoint.ry());
			}
		}
		else
		{
			//判断x,y轴的相对位移，取最大值
			if (abs(startPoint.rx() - endPoint.rx()) < abs(startPoint.ry() - endPoint.ry()))
				nDistance = abs(startPoint.rx() - endPoint.rx());
			else
				nDistance = abs(startPoint.ry() - endPoint.ry());

			if (startPoint.rx() - endPoint.rx() > 0)
				endPoint.setX(startPoint.rx() - nDistance);
			else
				endPoint.setX(startPoint.rx() + nDistance);

			if (startPoint.ry() - endPoint.ry() > 0)
				endPoint.setY(startPoint.ry() - nDistance);
			else
				endPoint.setY(startPoint.ry() + nDistance);
		}
	}

	m_endPoint = endPoint;

	addPoint(m_endPoint);
}

//设置绘图的颜色及尺寸
void CBaseShape::setDrawColor(QColor penColor, QColor brushColor, int nPenSize)
{
	m_penColor = penColor;
	m_brushColor = brushColor;
	m_nPenSize = nPenSize;
	if (m_nPenSize == 14)
	{		
		m_PenCapstyle = Qt::SquareCap;
	}
	else
	{
		m_PenCapstyle = Qt::RoundCap;
	}

}

void CBaseShape::setEraseSize(int nEraseSize)
{
	m_nEraseSize = nEraseSize;
}

//设置绘图的类型
void CBaseShape::setDrawType(DRAW_TYPE nDrawType)
{
	m_nDrawType = nDrawType;

}
void CBaseShape::setCapStyle(Qt::PenCapStyle PenCapstyle)
{
	m_PenCapstyle = PenCapstyle;
}

//设置文本框输入的内容
void CBaseShape::setDrawText(QRect rect, QString strText)
{
	m_strText = strText;
	m_rect = rect;
}

//获取起始点坐标
QPoint CBaseShape::getStartPoint()
{
	return m_startPoint;
}

//获取绘制图形终点坐标
QPoint CBaseShape::getEndPoint()
{
	return m_endPoint;
}

//获取画笔颜色
QColor CBaseShape::getPenColor()
{
	return m_penColor;
}

//获取填充色
QColor CBaseShape::getBrushColor()
{
	return  m_brushColor;
}

//获取画笔的尺寸信息
int CBaseShape::getPenSize()
{
	return m_nPenSize;
}

void CBaseShape::SetDrawImage(QImage * pDrawImage)
{
	m_pDrawImage = pDrawImage;
}

void CBaseShape::addPoint(QPoint point)
{
	return;
}

