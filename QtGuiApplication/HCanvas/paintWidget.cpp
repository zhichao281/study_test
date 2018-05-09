#include "paintWidget.h"  
#include <QDebug>
#include <QTimer>
#include <QImage>
CPaintWidget::CPaintWidget(QWidget *parent)
	:QGraphicsScene(parent), m_pShape(nullptr), m_shapeType(Draw_Rect)
{
	Init();

}

CPaintWidget::~CPaintWidget()
{
	//ָ���ͷ�
	foreach(CBaseShape *shape, m_currentStack)
	{
		SAFE_DELETE(shape);
	}
	foreach(CBaseShape *shape, m_redoStack)
	{
		SAFE_DELETE(shape);
	}
}

//�����ĳ�ʼ��
void CPaintWidget::Init()
{
	m_BrushColor = Qt::transparent;
	m_PenColor   = Qt::black;
	m_nPenSize   = 1;
	m_nEraseSize = 12;
	m_bStopPolygon = true;
	m_bStraight	   = false;
	m_bPressed     = false;
	m_pShape     = new CDrawPen();
	m_plainTextEdit.reset(new CTextEdit(nullptr));

	//���ÿ�����չ���������������ܵĻ�ȡ����Ŀռ䡣
	//setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	//setAttribute(Qt::WA_TranslucentBackground, true);

	//���ֿ������źŲ۵İ�
	connect(m_plainTextEdit.get(), SIGNAL(sig_draw_text(QRect, QString)), this, SLOT(slot_draw_text(QRect, QString))); //�����������źŲ۰�
}
//
////ͼ������¼�
//void CPaintWidget::paintEvent(QPaintEvent * event)
//{
//	QPainter painter(this);
//	painter.setBrush(Qt::transparent);
//	painter.setPen(Qt::transparent);   //���ƻ�������  
//	painter.drawRect(this->rect());
//
//	QImage image(this->size(), QImage::Format_ARGB32);
//	image.fill(qRgba(255, 255, 255, 0));
//	QPainter painterImage(&image);
//
//
//	//������״ͼ��
//	foreach(CBaseShape *shape, m_currentStack)
//	{
//		if (shape != nullptr)
//		{
//			QImage image1 = this->grab().toImage();
//			shape->m_pDrawImage = &image1;
//			shape->paintDrawItem(painter);
//		}
//	}
//
//	//painter.drawImage(this->rect(), image);
//}
//
//ͼ������¼�
void CPaintWidget::paintEvent(QPaintEvent * event)
{
	
	//QPainter painter(this->viewport());
	//painter.setBrush(Qt::transparent);
	//painter.setPen(Qt::transparent);   //���ƻ�������  
	//painter.drawRect(this->rect());

	//QImage DrawImage(this->size(),QImage::Format_ARGB32);
	//DrawImage.fill(qRgba(255, 255, 255, 0));
	//QPainter painterImage(&DrawImage);
	//painterImage.setRenderHint(QPainter::Antialiasing, true);// ��ֱֹ������ �;��
	//
	////������״ͼ��
	//foreach(CBaseShape *shape, m_currentStack)
	//{		
	//	shape->SetDrawImage(&DrawImage);
	//	shape->paintDrawItem(painterImage);
	//}

	//painter.drawImage(this->rect(), DrawImage);

}
//
//void CPaintWidget::mousePressEvent(QMouseEvent *event)
//{
//	//��ճ�����Ϣ
//	while (!m_redoStack.empty())
//	{
//		CBaseShape *pBaseShape = m_redoStack.top();
//		m_redoStack.pop();
//		delete pBaseShape;
//		pBaseShape = nullptr;
//	}
//
//	////////////Polygon���⴦��///////////////// 
//	if (event->button() == Qt::RightButton)
//	{
//		m_bStopPolygon = true;
//		return;
//	}
//	bool bres = polygonPressEvent(event);
//	if (bres == true)
//	{
//		return;
//	}
//	m_bStopPolygon = true;
//	m_bPressed = true;
//	////////////�����������⴦��///////////////// 
//	if (m_plainTextEdit->toPlainText().size()>0)
//	{
//		QRect rect;
//		QString strText;
//
//		rect = QRect(QPoint(m_plainTextEdit->x() + 5, m_plainTextEdit->y() + 5), QSize(m_plainTextEdit->width(), m_plainTextEdit->height()));
//		strText = m_plainTextEdit->toPlainText();
//		emit m_plainTextEdit->sig_draw_text(rect, strText);
//	}
//	m_plainTextEdit->hide();
//	m_plainTextEdit->clear();
//
//	//������״��ʼ��
//	switch (m_shapeType)
//	{
//		case Draw_Line:
//			m_pShape = new CDrawLine;
//			break;
//		case Draw_Rect:
//			m_pShape = new CDrawRect;
//			break;
//		case Draw_Pen:
//			m_pShape = new CDrawPen;
//			break;
//		case Draw_Ellipse:
//			m_pShape = new CDrawEllipse;
//			break;
//		case Draw_Erase:
//			m_pShape = new CDrawErase;
//			m_pShape->setEraseSize(m_nEraseSize);
//			break;
//		case Draw_Arrow:
//			m_pShape = new CDrawArrow;
//			break;
//		case Draw_Text:
//		{
//			m_plainTextEdit->move(event->pos());
//			m_plainTextEdit->show();
//			m_plainTextEdit->setFocus();
//			return;
//		}
//		default:
//			break;
//
//	}
//	if (m_pShape != NULL)
//	{ 
//		m_pShape->setDrawColor(m_PenColor, m_BrushColor, m_nPenSize);
//		m_pShape->setDrawPoint(event->pos(), event->pos() + QPoint(0, 1), m_bStraight);
//		
//		m_currentStack.push(m_pShape);
//	}
//	this->viewport()->update();
//	//update();
//
//}
//
//
//void CPaintWidget::mouseMoveEvent(QMouseEvent *event)
//{
//	if (m_bPressed == false)
//	{
//		QWidget::mouseMoveEvent(event);
//		return;
//	}
//	
//	////////////Polygon���⴦��/////////////////  
//	if (m_shapeType == Draw_Polygon)
//	{
//		//��鸸��ָ���ܷ�ת��Ϊ����ָ��
//		CDrawPolygon *pShape = dynamic_cast<CDrawPolygon *>(m_currentStack.top());
//		if (pShape != NULL)
//		{
//			QPoint *p = pShape->getLastPoint();
//			p->setX(event->x());
//			p->setY(event->y());
//			//update();	
//			this->viewport()->update();
//		}
//		return;
//	}
//
//	m_pShape->setDrawPoint(m_pShape->getStartPoint(), event->pos(), m_bStraight);
//	//update();
//	this->viewport()->update();
//}
//
//void CPaintWidget::mouseReleaseEvent(QMouseEvent *event)
//{
//	m_bPressed = false;
//	QWidget::mouseReleaseEvent(event);
//}



void CPaintWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	switch (m_shapeType)
	{
	case DRAW_TYPE::Draw_Line:
	{
		CDrawLine *line = new CDrawLine;
		m_pShape = line;
		addItem(line);
		break;
	}
	case DRAW_TYPE::Draw_Rect:
	{
		CDrawRect *rect = new CDrawRect;
		m_pShape = rect;
		addItem(rect);
		break;
	}
	}
	if (m_pShape) {
		m_pShape->startDraw(event);
		m_bPressed = true;
	}
	QGraphicsScene::mousePressEvent(event);
}

void CPaintWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_pShape && m_bPressed) {
		m_pShape->drawing(event);
	}
	QGraphicsScene::mouseMoveEvent(event);
}

void CPaintWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	m_bPressed = false;
	QGraphicsScene::mouseReleaseEvent(event);
}


void CPaintWidget::slot_set_straight(bool bStraight)
{
	m_bStraight = bStraight;
}

//
////��������ʱ��Ķ�������⴦��
//bool CPaintWidget::polygonPressEvent(QMouseEvent * event)
//{
//
//	/***********��ǰ����ͼ��Ϊ�����************/
//	if (m_shapeType == DRAW_TYPE::Draw_Polygon)
//	{
//
//		if (m_bStopPolygon == true || m_currentStack.isEmpty())
//		{
//			//��ʼ�㴦��
//			m_pShape = new CDrawPolygon;
//			CDrawPolygon *tmp = dynamic_cast<CDrawPolygon *>(m_pShape);
//			QPoint *p = new QPoint(event->pos());
//			tmp->addPoint(p);
//			QPoint *p2 = new QPoint(event->pos() + QPoint(0, 1));
//			tmp->addPoint(p2);
//			m_currentStack.push(m_pShape);
//			m_pShape->setDrawColor(m_PenColor, m_BrushColor, m_nPenSize);
//			m_bStopPolygon = false;
//		}
//		else
//		{
//			//�����㴦��
//			if (typeid(*m_currentStack.top()) != typeid(CDrawPolygon))
//			{
//				m_bStopPolygon = true;
//				return true;
//			}
//			QPoint *p = new QPoint(event->pos());
//			dynamic_cast<CDrawPolygon *>(m_pShape)->addPoint(p);
//		}
//		update();
//		return true;
//	}
//	return false;
//}

// ���û��ʵ������ʽ
void CPaintWidget::setDrawCursor()
{
	if (m_shapeType == DRAW_TYPE::Draw_Erase)
	{
		QCursor cursor;
		//����ͼƬ
		QPixmap pixmap(":/Image/Resources/Image/i_menu_eraser_d.png");
		//�����С
		QSize picSize(m_nEraseSize, m_nEraseSize);
		//����ͼƬ��������
		QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
		//������ʽ
		cursor = QCursor(scaledPixmap, -1, -1);
		//���������״
		//this->setCursor(cursor);
	}
	else
	{
		//this->setCursor(Qt::ArrowCursor);
	}


}

/**********************SLOT**********************/ 

void CPaintWidget::slot_set_penColor(QColor penColor)
{
	m_PenColor = penColor;
}

//�������ɫ
void CPaintWidget::slot_set_brushColor(QColor color)
{
	int tmp;
	int nAlpha;
	m_BrushColor.getRgb(&tmp, &tmp, &tmp, &nAlpha);
	m_BrushColor = color;
	m_BrushColor.setAlpha(nAlpha);

}

//������Ƥ����С
void CPaintWidget::slot_set_EraseSize(int nEraseSize)
{
	m_nEraseSize = nEraseSize;
	setDrawCursor();
}

void CPaintWidget::slot_set_shape(DRAW_TYPE new_shape)
{
	m_shapeType =(DRAW_TYPE)new_shape;
	setDrawCursor();

}

void CPaintWidget::slot_set_penSize(int nPenSize)
{
	m_nPenSize = nPenSize;
	setDrawCursor();

}


//����������Ϣ��Ϊ������Ϣ
void CPaintWidget::slot_draw_text(QRect rect, QString strText)
{
	m_pShape = new CDrawText;
	m_pShape->setDrawText(rect, strText);
	m_currentStack.push(m_pShape);
	update();
}

void CPaintWidget::solt_set_brushAlpha(int nAlpha)
{
	m_BrushColor.setAlpha((100 - nAlpha) * 255 / 100);
}

//����  
void CPaintWidget::slot_Undo()
{
	if (!m_currentStack.empty())
	{
		CBaseShape *tmp = m_currentStack.top();
		m_currentStack.pop();
		//QGraphicsItem *item = itemAt(0);
		//removeItem(tmp);
		m_redoStack.push(tmp);
	}
	//this->viewport()->update();
}

//�ָ�  
void CPaintWidget::slot_Redo()
{
	if (!m_redoStack.empty())
	{
		CBaseShape *tmp = m_redoStack.top();
		m_redoStack.pop();

		m_currentStack.push(tmp);
	}
	update();
}

void CPaintWidget::slot_Reset()
{
	m_BrushColor = Qt::transparent;
	m_PenColor = Qt::black;
	m_nPenSize = 1;
	m_currentStack.clear();
	m_redoStack.clear();
	m_bStopPolygon = true;
	update();
}
