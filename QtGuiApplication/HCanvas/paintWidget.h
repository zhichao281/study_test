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
	/** Ĭ�Ϲ��캯�� */
	explicit CPaintWidget(QWidget *parent = 0);

	/** Ĭ���������� */
	~CPaintWidget();

private:

	/**
	* Describe : ��ʼ��
	* Param	   : void
	* Return   : void
	*/
	void  Init();

	/*
	* Describe : ���û��ʵ������ʽ
	* Param	   : void
	* Return   : void
	*/
	void setDrawCursor();

	/**
	* Describe : ����ΰ��µ����⴦��
	* Param	   : void
	* Return   : void
	*/
	bool polygonPressEvent(QMouseEvent *event);


	//��д�¼�
protected:
	/**
	* Describe : �����¼�
	* Param	   : paint �������¼�ָ��
	* Return   : void
	*/
	void paintEvent(QPaintEvent *paint);

	/*
	* Describe : ����ƶ��¼�
	* Param	   : event ���ƶ��¼�ָ��
	* Return   : void
	*/
	void mouseMoveEvent(QMouseEvent *event);

	/**
	* Describe : ��갴���¼�
	* Param	   : event �������¼�ָ��
	* Return   : void
	*/
	void mousePressEvent(QMouseEvent *event);

	/**
	* Describe : ����ͷ��¼�
	* Param	   : event �ͷ��¼�ָ��
	* Return   : void
	*/
	void mouseReleaseEvent(QMouseEvent *event);


protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	//�źŲ�֮�۵Ķ���
public slots:
	/**
	* Describe : ����ǿ��X=Y �������� Բ��
	* Param	   : bStraight true ǿ��x=y,flase x yֵ�����
	* Return   : void
	*/
	void slot_set_straight(bool bStraight);

	/**
	* Describe : ���û�ͼ��״�Ĳ�
	* Param	   : new_shape ͼ����״ö��
	* Return   : void
	*/
	void slot_set_shape(DRAW_TYPE new_shape);

	/**
	* Describe : ���û�����ɫ
	* Param	   : penColor ������ɫ
	* Return   : void
	*/
	void slot_set_penColor(QColor penColor);

	/**
	* Describe : ���������ɫ
	* Param	   : brushColor ���ɫ
	* Return   : void
	*/
	void slot_set_brushColor(QColor brushColor);

	/**
	* Describe : ������Ƥ����С
	* Param	   : nEraseSize ��Ƥ����С
	* Return   : void
	*/
	void  slot_set_EraseSize(int nEraseSize);

	/**
	* Describe : ����������ϸ���ź�
	* Param	   : nPenSize ���ʳߴ�
	* Return   : void
	*/
	void slot_set_penSize(int nPenSize);

	/**
	* Describe : �������ɫ��͸����
	* Param	   : nAlpha ͸��ֵ 0-100
	* Return   : void
	*/
	void solt_set_brushAlpha(int nAlpha);



	/**
	* Describe : �����ı���������źŲ�
	* Param	   : rect :�ı������λ��, strText:�ı������������
	* Return   : void
	*/
	void slot_draw_text(QRect rect,QString strText);
	
	/**
	* Describe : ����
	* Param	   : void
	* Return   : void
	*/
	void slot_Undo();

	/**
	* Describe : ����
	* Param	   : void
	* Return   : void
	*/
	void slot_Redo();

	/**
	* Describe : ����
	* Param	   : void
	* Return   : void
	*/
	void slot_Reset();



private:
	DRAW_TYPE				m_shapeType;	//���û��Ƶ���״  
	QStack<CBaseShape *>	m_currentStack;	//���浱ǰ��ͼ�켣
	QStack<CBaseShape *>	m_redoStack;	//�����ָ���	
	CBaseShape				*m_pShape;		//��ǰ���Ƶ���״��ָ��
	
	QColor				m_PenColor;		//��ǰ������ɫ
	QColor				m_BrushColor;	//��ǰ�����ɫ
	QString				m_savePath;		//����·��


	int					m_nPenSize;		//��ǰ�ʵĴ�С
	int					m_nEraseSize;	//��ǰ��Ƥ���Ĵ�С
	bool				m_bStopPolygon;	//ֹͣ����εĻ���
	bool				m_bStraight;	//�Ƿ�ǿ��ֱ��
	bool                m_bPressed;     //����Ƿ���



	std::shared_ptr<CTextEdit>	 m_plainTextEdit;	//���������

};

