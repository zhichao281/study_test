#ifndef BKIMAGEWIDGET_H
#define BKIMAGEWIDGET_H

#include <QWidget>

class CBkImageWidget : public QWidget
{
	Q_OBJECT

public:
	CBkImageWidget(QWidget *parent=0);
	~CBkImageWidget();

private:

public:
	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���ñ���ͼƬ
	*/
	bool    SetBkImage(QString strFile);




public:

	QImage              m_bkImage;          //����ͼƬ
};

#endif // BKIMAGEWIDGET_H
