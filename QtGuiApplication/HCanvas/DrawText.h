/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file BaseShape.h
* @summary »æÖÆÎÄ±¾
*
* @version 1.0
* @author zhengzc@wangsu.com
* @date 2018-03-06 14:25:06
*
* @others
* @MODIFY    VERSION  YYYYMMDD    TITLE
* zhengzc     1.0     20180306     title
*
*/
#pragma once


#include "BaseShape.h"  
#include <QPainter>  
#include <QGraphicsTextItem>

class CDrawText : public CBaseShape, public QGraphicsTextItem
{
public:
	CDrawText();
	~CDrawText();
private:

	virtual void paintDrawItem(QPainter& paint) override;
	virtual int getDrawType() override;
	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);

};

