/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file DrawEllipse.h
* @summary 圆形绘制
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
#include <QGraphicsLineItem>
class CDrawPen : public CBaseShape, public QGraphicsLineItem
{
public:
	CDrawPen();
	 void paintDrawItem(QPainter& paint) override;
	virtual int getDrawType() override;

	/*
	* Author   : Zhengzc
	* DateTime : 2018-03-08
	* Describe : 添加点
	*/
	virtual void addPoint(QPoint  point) override;

	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);

private:

	QVector<QPoint >   m_vecPonitStack;  //保存画笔点坐标

};
