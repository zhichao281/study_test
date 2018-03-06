/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file BaseShape.h
* @summary 基本绘制形状
*
* @version 1.0
* @author zhengzc@wangsu.com
* @date 2018-03-05 14:25:06
*
* @others
* @MODIFY    VERSION  YYYYMMDD    TITLE
* zhengzc     1.0     20180305     title
*
*/


#pragma once

#include <QPoint>  
#include <QPainter>  
#include <QColor>  
#include <QWidget>
#include "type.h"



class CBaseShape
{
public:
	CBaseShape();
	void set_start(QPoint p);
	void set_end(QPoint p);
	void set_pos(QPoint, QPoint, bool);
	void set(QColor, QColor, int);

	void setDrawType(int nDrawType);

	void setCapStyle(Qt::PenCapStyle pcs);

	QPoint get_start();
	QPoint get_end();
	QColor get_color();
	QColor get_brush();
	int get_width();
	virtual void paint(QPainter& painter) = 0;
	virtual int get_DrawType() = 0;

	virtual int showShape(QPoint point) ;

	virtual void Set_Parent(QWidget *parent);

protected:
	QPoint m_startPoint;
	QPoint m_endPoint;
	QColor m_penColor;
	QColor m_brushColor;
	int					 m_nPenSize;
	Qt::PenCapStyle      m_PenCapstyle;

	int					  m_nDrawType;
};
