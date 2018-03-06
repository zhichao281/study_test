#pragma once
#include "BaseShape.h"  
#include <QPainter>  
class Pen : public CBaseShape
{
public:
	Pen();
	 void paint(QPainter& paint) override;
	virtual int get_DrawType() override;

};
