#include "DrawErase.h"

#include <QDebug>

CDrawErase::CDrawErase()
{
	m_nSize = 0;
}

void CDrawErase::drawerase(QImage imageErase, QPainter &paint, QPainter &paintErase)
{
	//��ȡͼ���׵�ַ��32λͼ
	int nWidth = m_pDrawImage->width();
	int nHeight = m_pDrawImage->height();

	if (m_nSize == 0 || m_nSize != m_vecEraseStack.size())
	{
		//����ͼƬ��С
		m_vecPoint.clear();
		int  lineNum_32 = 0;     //����

		uchar*    EraseImagebits_32 = imageErase.bits();
		uchar *pDrawImafeBits = m_pDrawImage->bits();

		for (int nY = 0; nY < nHeight; ++nY)
		{
			lineNum_32 = nY * nWidth * 4;
			for (int nX = 0; nX < nWidth; ++nX)
			{
				/*
				int r_32 = imagebits_32[lineNum_32 + nX * 4 + 2];
				int g_32 = imagebits_32[lineNum_32 + nX * 4 + 1];
				*/
				int b_32 = EraseImagebits_32[lineNum_32 + nX * 4];
				int Da_32 = pDrawImafeBits[lineNum_32 + nX * 4 + 3];
				if (b_32 == 255 && Da_32 != 0)
				{
					pDrawImafeBits[lineNum_32 + nX * 4 + 3] = 0;
					m_vecPoint.push_back(QPoint(nX, nY));
				}
			}
		}
		m_nSize = m_vecEraseStack.size();
	}
	else
	{
		uchar *pDrawImafeBits = m_pDrawImage->bits();
		foreach(QPoint point, m_vecPoint)
		{
			int nSize = point.y() * nWidth * 4 + point.x() * 4 + 3;
			pDrawImafeBits[nSize] = 0;
		}
	}
}

//void CDrawErase::paintDrawItem(QPainter &paint)
//{
//	clock_t start_time = clock();
//	paint.setCompositionMode(QPainter::CompositionMode_Clear);
//	QPen pen(Qt::transparent, m_nEraseSize);
//	pen.setCapStyle(Qt::RoundCap);
//	pen.setJoinStyle(Qt::RoundJoin);
//	paint.setPen(pen);
//	for (int i = 0; i < m_vecEraseStack.size() - 1; i++)
//	{
//		paint.drawLine(m_vecEraseStack[i].x(), m_vecEraseStack[i].y(), m_vecEraseStack[i + 1].x(), m_vecEraseStack[i + 1].y());  //�������е�������
//	}
//
//	paint.setCompositionMode(QPainter::CompositionMode_SourceOver);
//	
//	clock_t end_time = clock();
//	qDebug() << "size:" << m_vecEraseStack.size() <<  "erase time" << end_time - start_time;
//	return;
//}

void CDrawErase::paintDrawItem(QPainter &paint)
{
	clock_t start_time = clock();
	quint32 *pBits = (quint32*)m_pDrawImage->bits();
	
	if (m_nSize == 0 || m_nSize != m_vecEraseStack.size())
	{
		//����ͼƬ��С
		int nWidth = m_pDrawImage->width();
		int nHeight = m_pDrawImage->height();

		//������Ƥ���켣
		QImage imageErase(nWidth, nHeight, QImage::Format_ARGB32);
		QPainter painter(&imageErase);
		QPen pen(QColor(0xFF, 0xFF, 0xFF, 0xFF), m_nEraseSize);
		pen.setCapStyle(Qt::RoundCap);
		pen.setJoinStyle(Qt::RoundJoin);
		painter.setPen(pen);
		painter.setRenderHint(QPainter::Antialiasing, true);// ��ֱֹ������

		for (int i = 0; i < m_vecEraseStack.size() - 1; i++)
		{
			painter.drawLine(m_vecEraseStack[i].x(), m_vecEraseStack[i].y(), m_vecEraseStack[i + 1].x(), m_vecEraseStack[i + 1].y());  //�������е�������
		}

		quint32 *pBitsErase = (quint32*)imageErase.bits();
		m_vecBit.clear();
		//�ϳ�ͼƬ
		int nCnt = nWidth * nHeight;
		for (int i = 0; i < nCnt; ++i)
		{
			if (pBitsErase[i] == 0xFFFFFFFF && pBits[i] != 0xFFFFFF)
			{
				pBits[i] = 0;
				m_vecBit.push_back(i);
			}

		}
		m_nSize = m_vecEraseStack.size();
	}
	else
	{
		quint32 *pBits = (quint32*)m_pDrawImage->bits();
		foreach(int i, m_vecBit)
		{
			pBits[i] = 0;
		}
	}
	clock_t end_time = clock();
	qDebug() << "size:" << m_vecEraseStack.size() << "erase time" << end_time - start_time;
	return;
}

int CDrawErase::getDrawType()
{
	return DRAW_TYPE::Draw_Erase;
}

void CDrawErase::addPoint(QPoint point)
{
	//���Ը���һ������ͬ�ĵ�
	QVector<QPoint> vectPos = m_vecEraseStack;
	if (!vectPos.isEmpty())
	{
		if (vectPos.last() == point)
			return;
	}
	m_vecEraseStack.push_back(point);

}
