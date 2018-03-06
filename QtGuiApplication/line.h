#pragma once
#include <QPainter>  
#include "BaseShape.h"  
class Line : public CBaseShape
{
public:
	Line();
private:
	virtual void paint(QPainter& paint) override;
	virtual int get_DrawType() override;
};