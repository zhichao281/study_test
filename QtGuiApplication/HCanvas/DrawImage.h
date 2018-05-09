/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file DrawEllipse.h
* @summary ͼƬ
*
* @version 1.0
* @author zhengzc@wangsu.com
* @date 2018-03-07 14:25:06
*
* @others
* @MODIFY    VERSION  YYYYMMDD    TITLE
* zhengzc     1.0     20180307     title
*
*/



#pragma once
#include "BaseShape.h"  
#include <QPainter>  
class CDrawImage : public CBaseShape
{
public:
	CDrawImage();
	~CDrawImage();


private:

	virtual void paintDrawItem(QPainter& paint, int nWidth, int nHeight) override;
	virtual int getDrawType() override;

private:
	QVector<QPoint >   m_vecEraseStack;  //保存画笔点坐标

	int m_nSize;
	QVector<QPoint >		m_vecPoint;
	QVector<int >			m_vecBit;
	QImage  m_nNewIamge;
};

