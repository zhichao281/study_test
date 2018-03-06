/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file paintWidget.h
* @summary ���ڰװ�Ļ�ͼ��
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
	* Describe : �����¼�
	*/
	void paintEvent(QPaintEvent *);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ����ƶ��¼�
	*/
	void mouseMoveEvent(QMouseEvent *);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ��갴���¼�
	*/
	void mousePressEvent(QMouseEvent *);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ����ͷ��¼�
	*/
	void mouseReleaseEvent(QMouseEvent *);

	//�źŲ�֮�۵Ķ���
public slots:

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ���û�ͼ��״
	*/
	void slot_set_shape(DRAW_TYPE);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ���û�����ɫ
	*/
	void slot_set_penColor(QColor);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ���������ɫ
	*/
	void slot_set_brushColor(QColor);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ���û��ʳߴ�
	*/
	void slot_set_penWidth(int);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : ���û���͸����
	*/
	void solt_set_alpha(int);

	/*
	* Author   : zhengzc
	* DateTime : 2018-03-05
	* Describe : �����Ƿ�ֱ��
	*/
	void slot_set_straight(bool);


	void open_file();
	void save_file();
	void saveAs_file();
	void Undo();
	void Redo();
	void Reset();
private:
	DRAW_TYPE			m_shapeType;	//���û��Ƶ���״  
	QStack<CBaseShape *>		m_currentStack;	//���浱ǰ��ͼ�켣
	QStack<CBaseShape *>		m_redoStack;	//�����ָ���	
	CBaseShape				*m_pShape;		//��ǰ���Ƶ���״��ָ��
	
	QColor				m_PenColor;		//��ǰ������ɫ
	QColor				m_BrushColor;	//��ǰ�����ɫ
	QString				m_savePath;		//����·��

	int					m_nPenSize;		//��ǰ�ʵĴ�С
	bool				m_bStopPolygon; //ֹͣ����εĻ���
	bool				m_bStraight;	//�Ƿ�ǿ��ֱ��
};

