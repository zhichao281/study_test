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
	* Describe : 添加点
	*/
	void addPoint(QPoint *point);

	/*
	* Author   : Zhengzc
	* DateTime : 2018-3-08
	* Describe : 获取最后的端点
	*/
	QPoint *getLastPoint();

	int get_size();

	/*
	* Author   : Zhengzc
	* DateTime : 2018-3-08
	* Describe : 获取对应端点的坐标
	*/
	QPoint *index(int nPointIndex);
private:

	QVector<QPoint *>m_vecPolygonStack;  //保存多边形的各个端点坐标

};