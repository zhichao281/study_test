#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QObject>
#include <QMouseEvent>
#include <QWidget>
/**********����ͼƬ********************/
class ImageWidget : public QWidget
{
	Q_OBJECT

public:

	ImageWidget(QWidget *parent = 0);

	~ImageWidget();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ����ͼƬ
	*/
	void setPixmap(QString fileName);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ����ͼƬ
	*/
	void setPixmap(QPixmap pix);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ���óߴ�
	*/
	void setSize(int nWidth, int nHeight);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ��ȡͼƬ
	*/
	QPixmap getPixmap();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ����ͼƬ��Ϣ
	*/
	void  SetImageInfo(int nPenid);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ��ȡͼƬ��Ϣ
	*/
	int   GetImageInfo(int &nPenid);


	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : ��תͼƬ
	*/
	void  RotateImage(qreal angle = 90);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : ��תͼƬ
	*/
	qreal  GetRotate();


public:
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : ��ȡ���λ����Ϣ
	*/
	int countFlag(QPoint p, int row);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : ��������ʽ
	*/
	void setCursorType(int flag);

	int countRow(QPoint p);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : ���ñ༭״̬
	*/
	void SetEditState(bool bState);
protected:
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : �����¼�
	*/
	void paintEvent(QPaintEvent *);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ����ƶ��¼�
	*/
	void mouseMoveEvent(QMouseEvent *event);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ��갴���¼�
	*/
	void mousePressEvent(QMouseEvent *event);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : ����ͷ��¼�
	*/
	void mouseReleaseEvent(QMouseEvent *event);
	public slots:


private:
	QPixmap   m_pixmap;             //���ص�ͼƬ
	qreal     m_Angle;              //ѡ��Ƕ�
	int       rolatetY, rolatetX;    //XYѡ��ľ���
	int       oldY, oldX;
	QPoint    m_startPnt;           //���
	QPoint    m_endPnt;             //�յ�
	int      _curpos;               //���������ʱ��λ��
	bool      bFit;                 //ͼ���Ƿ�ƥ�䴰�ڳߴ�
	qreal     scale;                //ͼ������ֵ
	int       m_nMargin;            //���ڱ�Ե����
	int       m_nShadow_Width;      //��Ӱ���
	bool      m_bEditState;         //�Ƿ���ʾ�ɱ༭״̬
	int       m_nPenid;             //ͼƬ��Ӧ��Penid
	bool      m_bleftPressed;       //����Ƿ���

	int       m_nMarginWidth;


};


#endif // IMAGEWIDGET_H
