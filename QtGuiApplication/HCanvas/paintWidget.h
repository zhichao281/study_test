/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file paintWidget.h
* @summary 用于白板的绘图层
*
* @version 1.0
* @author zhengzc@wangsu.com
* @date 2018-03-05 14:25:06
*
* @others
* @MODIFY    VERSION  YYYYMMDD    TITLE
* zhengzc      1.0    20180305     title
*
*/


#pragma once
#pragma execution_character_set("utf-8")
#include <memory>

#include <QTextStream>  
#include <QFileDialog>  
#include <QMessageBox>  
#include <QMouseEvent>  
#include <QKeyEvent>  
#include <QWidget>  
#include <QBrush>  
#include <QStack>  
#include <QFile>  
#include <QPen>  

#include "DrawEllipse.h"  
#include "DrawPolygon.h"  
#include "BaseShape.h"  
#include "type.h"  
#include "DrawLine.h"  
#include "DrawRect.h"  
#include "DrawPen.h"  
#include "DrawErase.h"
#include "DrawText.h"
#include "DrawArrow.h"
#include "TextEdit.h"
#include <QGraphicsView>
class CPaintWidget : public QGraphicsScene
{
	Q_OBJECT
public:
	/** 默认构造函数 */
	explicit CPaintWidget(QWidget *parent = 0);

	/** 默认析构函数 */
	~CPaintWidget();

private:

	/**
	* Describe : 初始化
	* Param	   : void
	* Return   : void
	*/
	void  Init();

	/*
	* Describe : 设置画笔的鼠标样式
	* Param	   : void
	* Return   : void
	*/
	void setDrawCursor();

	/**
	* Describe : 多边形按下的特殊处理
	* Param	   : void
	* Return   : void
	*/
	bool polygonPressEvent(QMouseEvent *event);


	//重写事件
protected:
	/**
	* Describe : 绘制事件
	* Param	   : paint ：绘制事件指针
	* Return   : void
	*/
	void paintEvent(QPaintEvent *paint);

	/*
	* Describe : 鼠标移动事件
	* Param	   : event ：移动事件指针
	* Return   : void
	*/
	void mouseMoveEvent(QMouseEvent *event);

	/**
	* Describe : 鼠标按下事件
	* Param	   : event ：按下事件指针
	* Return   : void
	*/
	void mousePressEvent(QMouseEvent *event);

	/**
	* Describe : 鼠标释放事件
	* Param	   : event 释放事件指针
	* Return   : void
	*/
	void mouseReleaseEvent(QMouseEvent *event);


protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	//信号槽之槽的定义
public slots:
	/**
	* Describe : 设置强制X=Y 如正方形 圆形
	* Param	   : bStraight true 强制x=y,flase x y值不相关
	* Return   : void
	*/
	void slot_set_straight(bool bStraight);

	/**
	* Describe : 设置绘图形状的槽
	* Param	   : new_shape 图形形状枚举
	* Return   : void
	*/
	void slot_set_shape(DRAW_TYPE new_shape);

	/**
	* Describe : 设置画笔颜色
	* Param	   : penColor 画笔颜色
	* Return   : void
	*/
	void slot_set_penColor(QColor penColor);

	/**
	* Describe : 设置填充颜色
	* Param	   : brushColor 填充色
	* Return   : void
	*/
	void slot_set_brushColor(QColor brushColor);

	/**
	* Describe : 设置橡皮擦大小
	* Param	   : nEraseSize 橡皮擦大小
	* Return   : void
	*/
	void  slot_set_EraseSize(int nEraseSize);

	/**
	* Describe : 设置线条粗细的信号
	* Param	   : nPenSize 画笔尺寸
	* Return   : void
	*/
	void slot_set_penSize(int nPenSize);

	/**
	* Describe : 设置填充色的透明度
	* Param	   : nAlpha 透明值 0-100
	* Return   : void
	*/
	void solt_set_brushAlpha(int nAlpha);



	/**
	* Describe : 接受文本框输入的信号槽
	* Param	   : rect :文本输入框位置, strText:文本框的文字内容
	* Return   : void
	*/
	void slot_draw_text(QRect rect,QString strText);
	
	/**
	* Describe : 撤销
	* Param	   : void
	* Return   : void
	*/
	void slot_Undo();

	/**
	* Describe : 重做
	* Param	   : void
	* Return   : void
	*/
	void slot_Redo();

	/**
	* Describe : 重置
	* Param	   : void
	* Return   : void
	*/
	void slot_Reset();



private:
	DRAW_TYPE				m_shapeType;	//设置绘制的形状  
	QStack<CBaseShape *>	m_currentStack;	//保存当前绘图轨迹
	QStack<CBaseShape *>	m_redoStack;	//撤销恢复用	
	CBaseShape				*m_pShape;		//当前绘制的形状类指针
	
	QColor				m_PenColor;		//当前画笔颜色
	QColor				m_BrushColor;	//当前填充颜色
	QString				m_savePath;		//保存路径


	int					m_nPenSize;		//当前笔的大小
	int					m_nEraseSize;	//当前橡皮擦的大小
	bool				m_bStopPolygon;	//停止多边形的绘制
	bool				m_bStraight;	//是否强制直行
	bool                m_bPressed;     //鼠标是否按下



	std::shared_ptr<CTextEdit>	 m_plainTextEdit;	//文字输入框

};

