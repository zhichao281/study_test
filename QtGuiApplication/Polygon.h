#pragma once
#include "BaseShape.h"  
#include <QPolygon>  
#include <QPoint>  
#include <QVector>  

class Polygon : public CBaseShape
{
public:
	Polygon();
	~Polygon();
	virtual void paint(QPainter&);
	virtual int get_DrawType();
	void push(QPoint *);
	QPoint *top();
	int get_size();
	QPoint *index(int pos);
private:
	QVector<QPoint *>polygonStack;

};