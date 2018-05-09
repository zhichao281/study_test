#pragma once
#include "BaseShape.h"  
#include <QPolygon>  
#include <QPoint>  
#include <QVector>  

class CDrawPolygon : public CBaseShape
{
public:
	CDrawPolygon();
	~CDrawPolygon();
	virtual void paintDrawItem(QPainter&);

	virtual int getDrawType();
	/*
	* Author   : Zhengzc
	* DateTime : 2018-03-08
	* Describe : ��ӵ�
	*/
	void addPoint(QPoint *point);

	/*
	* Author   : Zhengzc
	* DateTime : 2018-3-08
	* Describe : ��ȡ���Ķ˵�
	*/
	QPoint *getLastPoint();

	int get_size();

	/*
	* Author   : Zhengzc
	* DateTime : 2018-3-08
	* Describe : ��ȡ��Ӧ�˵������
	*/
	QPoint *index(int nPointIndex);
private:

	QVector<QPoint *>m_vecPolygonStack;  //�������εĸ����˵�����

};