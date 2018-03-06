#pragma once
#include "BaseShape.h"  
class Ellipse : public CBaseShape
{
public:
	Ellipse();
private: 
	virtual void paint(QPainter& paint) override;
	virtual int get_DrawType() override;
};


