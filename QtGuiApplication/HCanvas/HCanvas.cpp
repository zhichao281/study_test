#include "HCanvas.h"
#include <QPainter>

#include <QGraphicsView>

HCanvas::HCanvas(QWidget *parent) : QWidget(parent)
{
	//初始化参数
	_Init();
	
	//信号槽绑定
	SignalBinding();
}
//默认析构函数
HCanvas::~HCanvas()
{
}


/**
* @brief 初始化
*/
void HCanvas::_Init()
{
	this->setFixedSize(950, 500);
	//设置可以伸展或者收缩，尽可能的获取额外的空间。
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


	//设置背景图填充满
	setAutoFillBackground(true);  

	m_drawWidget.reset(new CPaintWidget(this));

	QGraphicsView *view = new QGraphicsView(m_drawWidget.get(), this);
	view->setGeometry(0, 0, this->width(), this->height());

}
void HCanvas::SignalBinding()
{
	//改变是否笔直绘画的信号槽绑定
	connect(this, SIGNAL(sig_change_straight(bool)),	m_drawWidget.get(), SLOT(slot_set_straight(bool)));
	
	//设置绘图形状的信号槽绑定
	connect(this, SIGNAL(sig_set_shape(DRAW_TYPE)),			m_drawWidget.get(), SLOT(slot_set_shape(DRAW_TYPE)));
	
	//设置绘图形状的信号槽绑定
	connect(this, SIGNAL(sig_set_shape(DRAW_TYPE)), this, SLOT(test(DRAW_TYPE)));

	//设置画笔颜色调整信号槽绑定
	connect(this, SIGNAL(sig_set_penColor(QColor)),		m_drawWidget.get(), SLOT(slot_set_penColor(QColor)));

	//设置填充颜色调整的信号槽绑定
	connect(this, SIGNAL(sig_set_brushColor(QColor)),	m_drawWidget.get(), SLOT(slot_set_brushColor(QColor)));

	//设置线条粗细的信号槽绑定
	connect(this, SIGNAL(sig_set_penSize(int)),			m_drawWidget.get(), SLOT(slot_set_penSize(int)));
	
	//设置橡皮擦大小的信号槽绑定
	connect(this, SIGNAL(sig_set_EraseSize(int)), m_drawWidget.get(), SLOT(slot_set_EraseSize(int)));

	//设置填充色的透明度的信号槽绑定
	connect(this, SIGNAL(sig_set_brushAlpha(int)),		m_drawWidget.get(), SLOT(solt_set_brushAlpha(int)));

	//撤销的信号槽绑定
	connect(this, SIGNAL(sig_Undo()),					m_drawWidget.get(), SLOT(slot_Undo()));
	
	//重做的信号槽绑定
	connect(this, SIGNAL(sig_Redo()),					m_drawWidget.get(), SLOT(slot_Redo()));
	
	//重置的信号槽绑定
	connect(this, SIGNAL(sig_Reset()),					m_drawWidget.get(), SLOT(slot_Reset()));

}

void HCanvas::test(DRAW_TYPE n1)
{

	int n2 = n1;
}
/**
* @brief 设置背景图片
* @param strFile   图片路径
* @return
*/
bool HCanvas::setBackgroundImage(QString strFile)
{
	QImage backgroundImage;
	bool bRes = backgroundImage.load(strFile);
	if ( bRes)
	{
		//缩放图片 等比例 不失真
		backgroundImage = backgroundImage.scaled(size(), Qt::IgnoreAspectRatio,
			Qt::SmoothTransformation);
		QPalette pal(palette());
		pal.setBrush(QPalette::Window, QBrush(backgroundImage));
		this->setPalette(pal);
		return true;
	}
	return false;
}

/**
* @brief 获取画布内容
* @param pixmap        图片
*/
void HCanvas::GetImage(QPixmap &pixmap)
{
	pixmap = this->grab();
}


