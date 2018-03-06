#pragma once

#include "BaseShape.h"  
#include <QPainter>  

class Rect : public CBaseShape
{
public:
	Rect();
private:
	virtual void paint(QPainter& paint) override;
	virtual int get_DrawType() override;
};
