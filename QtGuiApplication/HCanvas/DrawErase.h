/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file BaseShape.h
* @summary ��Ƥ������
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
class CDrawErase : public CBaseShape
{
public:
	CDrawErase();

	virtual void paintDrawItem(QPainter& paint) override;
	virtual int getDrawType() override;
	/*
	* Author   : Zhengzc
	* DateTime : 2018-03-08
	* Describe : ��ӵ�
	*/
	virtual void addPoint(QPoint  point) override;


	void drawerase(QImage imageErase, QPainter &paint, QPainter &paintErase);

private:

	QVector<QPoint >   m_vecEraseStack;  //���滭�ʵ�����

	int m_nSize;
	QVector<QPoint >		m_vecPoint;
	QVector<int >			m_vecBit;
};


