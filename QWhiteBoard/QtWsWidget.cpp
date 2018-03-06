
#include <windows.h>
#include <Winuser.h>
#pragma comment (lib, "User32.lib")
#include "QtWsWidget.h"
QtWsWidget::QtWsWidget(QWidget *parent)
	: QWidget(parent)
{
	this->setupUi(this);
}

QtWsWidget::~QtWsWidget()
{
}


void QtWsWidget::WhiteBoard_Create(HWND hfather, int nX, int nY, int nWidth, int nHight)
{
	if (hfather!=nullptr)
	{
		SetParent((HWND)this->winId(), hfather);
	}
	
	this->show();
	this->raise();
	this->move(nX, nY);
	

	

}