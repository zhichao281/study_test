


#pragma once


#include "BaseShape.h"  
#include <QPainter>  
#include <QLineEdit>

class CDrawText : public CBaseShape,public QLineEdit
{
public:
	CDrawText();
	~CDrawText();
private:
	virtual void paint(QPainter& paint) override;
	virtual int get_DrawType() override;
	virtual int showShape(QPoint point) override ;
	virtual void Set_Parent(QWidget *parent)override;


	virtual void focusInEvent(QFocusEvent *e);
	virtual void focusOutEvent(QFocusEvent *e);


private:
	bool bFocus;
};

