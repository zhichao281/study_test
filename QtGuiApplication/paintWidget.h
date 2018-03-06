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

#include "ellipse.h"  
#include "polygon.h"  
#include "BaseShape.h"  
#include "type.h"  
#include "line.h"  
#include "rect.h"  
#include "pen.h"  
#include "CErase.h"
#include "DrawText.h"
class CPaintWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CPaintWidget(QWidget *parent = 0);
protected:
	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 绘制事件
	*/
	void paintEvent(QPaintEvent *);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 鼠标移动事件
	*/
	void mouseMoveEvent(QMouseEvent *);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 鼠标按下事件
	*/
	void mousePressEvent(QMouseEvent *);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 鼠标释放事件
	*/
	void mouseReleaseEvent(QMouseEvent *);

	//信号槽之槽的定义
public slots:

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 设置绘图形状
	*/
	void slot_set_shape(DRAW_TYPE);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 设置画笔颜色
	*/
	void slot_set_penColor(QColor);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 设置填充颜色
	*/
	void slot_set_brushColor(QColor);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 设置画笔尺寸
	*/
	void slot_set_penWidth(int);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 设置画笔透明度
	*/
	void solt_set_alpha(int);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : 设置是否直行
	*/
	void slot_set_straight(bool);


	void open_file();
	void save_file();
	void saveAs_file();
	void Undo();
	void Redo();
	void Reset();
private:
	DRAW_TYPE			m_shapeType;	//设置绘制的形状  
	QStack<CBaseShape *>		m_currentStack;	//保存当前绘图轨迹
	QStack<CBaseShape *>		m_redoStack;	//撤销恢复用	
	CBaseShape				*m_pShape;		//当前绘制的形状类指针
	
	QColor				m_PenColor;		//当前画笔颜色
	QColor				m_BrushColor;	//当前填充颜色
	QString				m_savePath;		//保存路径

	int					m_nPenSize;		//当前笔的大小
	bool				m_bStopPolygon; //停止多边形的绘制
	bool				m_bStraight;	//是否强制直行
};

