
#include "BaseShape.h"  

#include <QDebug>
//���캯��
CBaseShape::CBaseShape()
	:m_startPoint(QPoint(0, 0)), m_endPoint(QPoint(0, 0))
{
	m_PenCapstyle= Qt::RoundCap;
}

//��������
CBaseShape::~CBaseShape()
{

}

//����ͼ�ε���ʼ��
void CBaseShape::setStartPoint(QPoint startPoint)
{
	m_startPoint = startPoint;
}

//����ͼ�εĽ�����
void CBaseShape::setEndPoint(QPoint endPoint)
{
	m_endPoint = endPoint;
}

//���û���������Ϣ
void CBaseShape::setDrawPoint(QPoint startPoint, QPoint endPoint, bool bStraight)
{
	m_startPoint = startPoint;
	int nDistance; //���λ��
	
	if (bStraight )
	{
		//�����ֱ�߾�ǿ��Ϊˮƽ���ߴ�ֱ
		if (getDrawType() == DRAW_TYPE::Draw_Line)
		{
			//�ж�x,y������λ�ƣ�ȡ���ֵ
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
			//�ж�x,y������λ�ƣ�ȡ���ֵ
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

//���û�ͼ����ɫ���ߴ�
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

//���û�ͼ������
void CBaseShape::setDrawType(DRAW_TYPE nDrawType)
{
	m_nDrawType = nDrawType;

}
void CBaseShape::setCapStyle(Qt::PenCapStyle PenCapstyle)
{
	m_PenCapstyle = PenCapstyle;
}

//�����ı������������
void CBaseShape::setDrawText(QRect rect, QString strText)
{
	m_strText = strText;
	m_rect = rect;
}

//��ȡ��ʼ������
QPoint CBaseShape::getStartPoint()
{
	return m_startPoint;
}

//��ȡ����ͼ���յ�����
QPoint CBaseShape::getEndPoint()
{
	return m_endPoint;
}

//��ȡ������ɫ
QColor CBaseShape::getPenColor()
{
	return m_penColor;
}

//��ȡ���ɫ
QColor CBaseShape::getBrushColor()
{
	return  m_brushColor;
}

//��ȡ���ʵĳߴ���Ϣ
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

