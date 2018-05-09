#pragma once

#include "BaseShape.h"  
#include <QPainter>  
#include <QGraphicsRectItem>
class CDrawRect : public CBaseShape, public QGraphicsRectItem
{
public:
	CDrawRect();
private:
	virtual void paintDrawItem(QPainter& paint) override;
	virtual int getDrawType() override;

	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);

};
