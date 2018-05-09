/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file BaseShape.h
* @summary ����������״��
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
	/** Ĭ�Ϲ��캯�� */
	CBaseShape();

	/** Ĭ���������� */
	~CBaseShape();   

	/*
	* Describe : ����ͼ�ε���ʼ��
	* Param	   : startPoint ����ʼ��
	* Return   : void
	*/
	void setStartPoint(QPoint startPoint);

	/**
	* Describe : ����ͼ�εĽ�����
	* Param	   : endPoint ���յ�
	* Return   : void
	*/
	void setEndPoint(QPoint endPoint);

	/**
	* Describe : ���û���������Ϣ
	* Param	   : startPoint :��ʼ��,endPoint:������,bStraight:ǿ�Ƶȱ���
	* Return   : void
	*/
	void setDrawPoint(QPoint startPoint, QPoint endPoint , bool bStraight);
	
	/**
	* Describe : ���û�ͼ����ɫ���ߴ�
	* Param	   : penColor :�ʵ���ɫ,brushColor:���ɫ,nPenSize:�ʵĴ�С
	* Return   : void
	*/
	void setDrawColor(QColor penColor, QColor brushColor, int nPenSize);

	/**
	* Describe : ������Ƥ����С
	* Param	   : nEraseSize ��Ƥ����С
	* Return   : void
	*/
	void  setEraseSize(int nEraseSize);

	/**
	* Describe : ���û�ͼ������
	* Param	   : nDrawType :ͼ������ö��
	* Return   : void
	*/
	void setDrawType(DRAW_TYPE nDrawType);

	/**
	* Describe : ���û��Ƶ��߶α�ñ����
	* Param	   : PenCapstyle : ��ñ����
	* Return   : void
	*/
	void setCapStyle(Qt::PenCapStyle PenCapstyle);

	/**
	* Describe : �����ı������������
	* Param	   : rect : �����λ��,strText:������ı�
	* Return   : void
	*/
	void setDrawText(QRect rect, QString strText);

	/**
	* Describe : ��ȡ��ʼ������
	* Param	   : void
	* Return   : QPoint:��ʼ������
	*/
	QPoint getStartPoint();

	/**
	* Describe : ��ȡ����ͼ���յ�����
	* Param	   : void
	* Return   : QPoint:�յ�����
	*/
	QPoint getEndPoint();

	/**
	* Describe : ��ȡ������ɫ
	* Param	   : void
	* Return   : QColor:������ɫ
	*/
	QColor getPenColor();

	/**
	* Describe : ��ȡ���ɫ
	* Param	   : void
	* Return   : QColor��ȡ���ɫ
	*/
	QColor getBrushColor();

	/**
	* Describe : ��ȡ���ʵĳߴ���Ϣ
	* Param	   : void
	* Return   : int  : ���ʳߴ�
	*/
	int getPenSize();

	/**
	* Describe : ���û�ͼ��ͼƬ
	* Param	   : pDrawImage  ��ͼָ��
	* Return   : void
	*/
	void SetDrawImage(QImage * pDrawImage);
	//�麯��
public:
	/**
	* Describe : ��д��ͼ�¼�
	* Param	   : void
	* Return   : void
	*/
	virtual void paintDrawItem(QPainter& painter) = 0;

	virtual void startDraw(QGraphicsSceneMouseEvent * event) = 0;
	
	virtual void drawing(QGraphicsSceneMouseEvent * event) = 0;
	/**
	* Describe : ��ȡ���Ƶ�ͼ������
	* Param	   : void
	* Return   : int  : ���Ƶ�ͼ��ö��
	*/
	virtual int getDrawType() = 0;

	/**
	* Describe : ��ӵ����굽������
	* Param	   : point : Ҫ��ӵĵ������
	* Return   : void
	*/
	virtual void addPoint(QPoint  point);


public:
		
	QImage * m_pDrawImage;


protected:
	QPoint   m_startPoint;  //��ʼ������
	QPoint   m_endPoint;	//�յ�����		

	QColor   m_penColor;	//������ɫ
	QColor	 m_brushColor;  //���ɫ

	int		 m_nPenSize;	//���ʳߴ�
	int      m_nEraseSize;  //��Ƥ����С

	DRAW_TYPE	m_nDrawType; //��ͼ���

	QString  m_strText;		//�ı�����������

	QRect     m_rect;		//�ı�������λ��


	Qt::PenCapStyle      m_PenCapstyle;//���ʵıʶ���ʽ
};
