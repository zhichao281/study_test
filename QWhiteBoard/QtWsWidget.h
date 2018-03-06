#pragma once

#include <QWidget>
#include "ui_QtWsWidget.h"
#include "HSingleton.h"

class QtWsWidget : public QWidget,public Ui::QtWsWidget
{
	Q_OBJECT

public:
	QtWsWidget(QWidget *parent = Q_NULLPTR);
	~QtWsWidget();


public:
	void WhiteBoard_Create(HWND hfather, int nX, int nY, int nWidth, int nHight);

};
#define gblQtWsWidgetGet HSingletonTemplatePtr<QtWsWidget>::get()