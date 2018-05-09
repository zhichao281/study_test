#include "HCanvas.h"
#include <QPainter>

#include <QGraphicsView>

HCanvas::HCanvas(QWidget *parent) : QWidget(parent)
{
	//��ʼ������
	_Init();
	
	//�źŲ۰�
	SignalBinding();
}
//Ĭ����������
HCanvas::~HCanvas()
{
}


/**
* @brief ��ʼ��
*/
void HCanvas::_Init()
{
	this->setFixedSize(950, 500);
	//���ÿ�����չ���������������ܵĻ�ȡ����Ŀռ䡣
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


	//���ñ���ͼ�����
	setAutoFillBackground(true);  

	m_drawWidget.reset(new CPaintWidget(this));

	QGraphicsView *view = new QGraphicsView(m_drawWidget.get(), this);
	view->setGeometry(0, 0, this->width(), this->height());

}
void HCanvas::SignalBinding()
{
	//�ı��Ƿ��ֱ�滭���źŲ۰�
	connect(this, SIGNAL(sig_change_straight(bool)),	m_drawWidget.get(), SLOT(slot_set_straight(bool)));
	
	//���û�ͼ��״���źŲ۰�
	connect(this, SIGNAL(sig_set_shape(DRAW_TYPE)),			m_drawWidget.get(), SLOT(slot_set_shape(DRAW_TYPE)));
	
	//���û�ͼ��״���źŲ۰�
	connect(this, SIGNAL(sig_set_shape(DRAW_TYPE)), this, SLOT(test(DRAW_TYPE)));

	//���û�����ɫ�����źŲ۰�
	connect(this, SIGNAL(sig_set_penColor(QColor)),		m_drawWidget.get(), SLOT(slot_set_penColor(QColor)));

	//���������ɫ�������źŲ۰�
	connect(this, SIGNAL(sig_set_brushColor(QColor)),	m_drawWidget.get(), SLOT(slot_set_brushColor(QColor)));

	//����������ϸ���źŲ۰�
	connect(this, SIGNAL(sig_set_penSize(int)),			m_drawWidget.get(), SLOT(slot_set_penSize(int)));
	
	//������Ƥ����С���źŲ۰�
	connect(this, SIGNAL(sig_set_EraseSize(int)), m_drawWidget.get(), SLOT(slot_set_EraseSize(int)));

	//�������ɫ��͸���ȵ��źŲ۰�
	connect(this, SIGNAL(sig_set_brushAlpha(int)),		m_drawWidget.get(), SLOT(solt_set_brushAlpha(int)));

	//�������źŲ۰�
	connect(this, SIGNAL(sig_Undo()),					m_drawWidget.get(), SLOT(slot_Undo()));
	
	//�������źŲ۰�
	connect(this, SIGNAL(sig_Redo()),					m_drawWidget.get(), SLOT(slot_Redo()));
	
	//���õ��źŲ۰�
	connect(this, SIGNAL(sig_Reset()),					m_drawWidget.get(), SLOT(slot_Reset()));

}

void HCanvas::test(DRAW_TYPE n1)
{

	int n2 = n1;
}
/**
* @brief ���ñ���ͼƬ
* @param strFile   ͼƬ·��
* @return
*/
bool HCanvas::setBackgroundImage(QString strFile)
{
	QImage backgroundImage;
	bool bRes = backgroundImage.load(strFile);
	if ( bRes)
	{
		//����ͼƬ �ȱ��� ��ʧ��
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
* @brief ��ȡ��������
* @param pixmap        ͼƬ
*/
void HCanvas::GetImage(QPixmap &pixmap)
{
	pixmap = this->grab();
}


