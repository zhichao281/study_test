#pragma once

#include "BaseShape.h"  
#include <QPainter>  
class CErase : public CBaseShape
{
public:
	CErase();
	~CErase();
	virtual void paint(QPainter& paint) override;
	virtual int get_DrawType() override;
};


