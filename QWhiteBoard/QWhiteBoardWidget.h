#pragma once
#include <QWidget>
#include "HSingleton.h"
class QWhiteBoardWidget :public QWidget
{
	Q_OBJECT
public:
	QWhiteBoardWidget();
	~QWhiteBoardWidget();



};



#define gblWhiteWidgetGet HSingletonTemplatePtr<QWhiteBoardWidget>::get()
