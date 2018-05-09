/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file BaseShape.h
* @summary 基本绘制形状类
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
#include <QString>
#include <QGraphicsSceneMouseEvent>
#include <QtGui>
#include "type.h"
#include <QGraphicsItem>

/** CBaseShape */
class CBaseShape 
{
public:
	/** 默认构造函数 */
	CBaseShape();

	/** 默认析构函数 */
	~CBaseShape();   

	/*
	* Describe : 设置图形的起始点
	* Param	   : startPoint ：起始点
	* Return   : void
	*/
	void setStartPoint(QPoint startPoint);

	/**
	* Describe : 设置图形的结束点
	* Param	   : endPoint ：终点
	* Return   : void
	*/
	void setEndPoint(QPoint endPoint);

	/**
	* Describe : 设置绘制坐标信息
	* Param	   : startPoint :起始点,endPoint:结束点,bStraight:强制等比例
	* Return   : void
	*/
	void setDrawPoint(QPoint startPoint, QPoint endPoint , bool bStraight);
	
	/**
	* Describe : 设置绘图的颜色及尺寸
	* Param	   : penColor :笔的颜色,brushColor:填充色,nPenSize:笔的大小
	* Return   : void
	*/
	void setDrawColor(QColor penColor, QColor brushColor, int nPenSize);

	/**
	* Describe : 设置橡皮擦大小
	* Param	   : nEraseSize 橡皮擦大小
	* Return   : void
	*/
	void  setEraseSize(int nEraseSize);

	/**
	* Describe : 设置绘图的类型
	* Param	   : nDrawType :图形类型枚举
	* Return   : void
	*/
	void setDrawType(DRAW_TYPE nDrawType);

	/**
	* Describe : 设置绘制的线段笔帽类型
	* Param	   : PenCapstyle : 笔帽类型
	* Return   : void
	*/
	void setCapStyle(Qt::PenCapStyle PenCapstyle);

	/**
	* Describe : 设置文本框输入的内容
	* Param	   : rect : 输入框位置,strText:输入框文本
	* Return   : void
	*/
	void setDrawText(QRect rect, QString strText);

	/**
	* Describe : 获取起始点坐标
	* Param	   : void
	* Return   : QPoint:起始点坐标
	*/
	QPoint getStartPoint();

	/**
	* Describe : 获取绘制图形终点坐标
	* Param	   : void
	* Return   : QPoint:终点坐标
	*/
	QPoint getEndPoint();

	/**
	* Describe : 获取画笔颜色
	* Param	   : void
	* Return   : QColor:画笔颜色
	*/
	QColor getPenColor();

	/**
	* Describe : 获取填充色
	* Param	   : void
	* Return   : QColor获取填充色
	*/
	QColor getBrushColor();

	/**
	* Describe : 获取画笔的尺寸信息
	* Param	   : void
	* Return   : int  : 画笔尺寸
	*/
	int getPenSize();

	/**
	* Describe : 设置绘图的图片
	* Param	   : pDrawImage  绘图指针
	* Return   : void
	*/
	void SetDrawImage(QImage * pDrawImage);
	//虚函数
public:
	/**
	* Describe : 重写绘图事件
	* Param	   : void
	* Return   : void
	*/
	virtual void paintDrawItem(QPainter& painter) = 0;

	virtual void startDraw(QGraphicsSceneMouseEvent * event) = 0;
	
	virtual void drawing(QGraphicsSceneMouseEvent * event) = 0;
	/**
	* Describe : 获取绘制的图形类型
	* Param	   : void
	* Return   : int  : 绘制的图形枚举
	*/
	virtual int getDrawType() = 0;

	/**
	* Describe : 添加点坐标到容器内
	* Param	   : point : 要添加的点的坐标
	* Return   : void
	*/
	virtual void addPoint(QPoint  point);


public:
		
	QImage * m_pDrawImage;


protected:
	QPoint   m_startPoint;  //起始点坐标
	QPoint   m_endPoint;	//终点坐标		

	QColor   m_penColor;	//画笔颜色
	QColor	 m_brushColor;  //填充色

	int		 m_nPenSize;	//画笔尺寸
	int      m_nEraseSize;  //橡皮擦大小

	DRAW_TYPE	m_nDrawType; //绘图类别

	QString  m_strText;		//文本输入框的文字

	QRect     m_rect;		//文本输入框的位置


	Qt::PenCapStyle      m_PenCapstyle;//画笔的笔端样式
};
