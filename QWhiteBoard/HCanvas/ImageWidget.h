#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QObject>
#include <QMouseEvent>
#include <QWidget>
/**********插入图片********************/
class ImageWidget : public QWidget
{
	Q_OBJECT

public:

	ImageWidget(QWidget *parent = 0);

	~ImageWidget();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 设置图片
	*/
	void setPixmap(QString fileName);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 设置图片
	*/
	void setPixmap(QPixmap pix);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 设置尺寸
	*/
	void setSize(int nWidth, int nHeight);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 获取图片
	*/
	QPixmap getPixmap();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 设置图片信息
	*/
	void  SetImageInfo(int nPenid);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 获取图片信息
	*/
	int   GetImageInfo(int &nPenid);


	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 旋转图片
	*/
	void  RotateImage(qreal angle = 90);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 旋转图片
	*/
	qreal  GetRotate();


public:
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 获取鼠标位置信息
	*/
	int countFlag(QPoint p, int row);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 设置鼠标格式
	*/
	void setCursorType(int flag);

	int countRow(QPoint p);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 设置编辑状态
	*/
	void SetEditState(bool bState);
protected:
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 绘制事件
	*/
	void paintEvent(QPaintEvent *);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 鼠标移动事件
	*/
	void mouseMoveEvent(QMouseEvent *event);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 鼠标按下事件
	*/
	void mousePressEvent(QMouseEvent *event);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 鼠标释放事件
	*/
	void mouseReleaseEvent(QMouseEvent *event);
	public slots:


private:
	QPixmap   m_pixmap;             //加载的图片
	qreal     m_Angle;              //选择角度
	int       rolatetY, rolatetX;    //XY选择的距离
	int       oldY, oldX;
	QPoint    m_startPnt;           //起点
	QPoint    m_endPnt;             //终点
	int      _curpos;               //标记鼠标左击时的位置
	bool      bFit;                 //图像是否匹配窗口尺寸
	qreal     scale;                //图像缩放值
	int       m_nMargin;            //窗口边缘距离
	int       m_nShadow_Width;      //阴影宽度
	bool      m_bEditState;         //是否显示可编辑状态
	int       m_nPenid;             //图片对应的Penid
	bool      m_bleftPressed;       //鼠标是否按下

	int       m_nMarginWidth;


};


#endif // IMAGEWIDGET_H
