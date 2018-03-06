#include "paintWidget.h"  
#include <QDebug>
CPaintWidget::CPaintWidget(QWidget *parent)
	:QWidget(parent), m_pShape(nullptr), m_shapeType(Draw_Rect)
{
	m_BrushColor = Qt::transparent;
	m_PenColor = Qt::black;
	m_nPenSize = 1;
	m_bStopPolygon = true;
	m_bStraight = false;
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

void CPaintWidget::paintEvent(QPaintEvent *)
{

	QPainter paint(this);
	paint.setBrush(Qt::transparent);
	paint.setPen(Qt::transparent);   //绘制画板区域  
	paint.drawRect(0, 0, size().width(), size().height());
	foreach(CBaseShape *shape, m_currentStack)
	{
		shape->paint(paint);
	}



}

void CPaintWidget::mousePressEvent(QMouseEvent *e)
{
	while (!m_redoStack.empty())
	{
		CBaseShape *tmp = m_redoStack.top();
		m_redoStack.pop();
		delete tmp;
	}

	////////////Polygon特殊处理/////////////////  
	if (e->button() == Qt::RightButton)
	{
		m_bStopPolygon = true;
		return;
	}
	if (m_shapeType == Draw_Polygon)
	{
		if (m_bStopPolygon == true || m_currentStack.isEmpty())
		{
			m_pShape = new Polygon;
			Polygon *tmp = dynamic_cast<Polygon *>(m_pShape);
			QPoint *p = new QPoint(e->pos());
			tmp->push(p);
			QPoint *p2 = new QPoint(e->pos() + QPoint(0, 1));
			tmp->push(p2);
			m_currentStack.push(m_pShape);
			m_pShape->set(m_PenColor, m_BrushColor, m_nPenSize);
			m_bStopPolygon = false;
		}
		else
		{
			if (typeid(*m_currentStack.top()) != typeid(Polygon))
			{
				m_bStopPolygon = true;
				return;
			}
			QPoint *p = new QPoint(e->pos());
			dynamic_cast<Polygon *>(m_pShape)->push(p);
		}
		update();
		return;
	}
	m_bStopPolygon = true;
	switch (m_shapeType)
	{
	case Draw_Line:
		m_pShape = new Line;
		break;
	case Draw_Rect:
		m_pShape = new Rect;
		break;
	case Draw_Pen:
		m_pShape = new Pen;
		break;
	case Draw_Ellipse:
		m_pShape = new Ellipse;
		break;
	case Draw_Erase:
		m_pShape = new CErase;
		break;
	case Draw_Text:
		m_pShape = new CDrawText;
		m_pShape->Set_Parent(this);
		break;
		
	}
	if (m_pShape != NULL)
	{
		if (m_shapeType == Draw_Pen || m_shapeType == Draw_Erase)
		{
			CBaseShape *zero = new Pen;
			zero->set_start(QPoint(0, 0));
			zero->set_end(QPoint(0, 0));
			m_currentStack.push(zero);

		}//Pen 制造间隔点  
		m_pShape->set(m_PenColor, m_BrushColor, m_nPenSize);
		m_pShape->set_pos(e->pos(), e->pos() + QPoint(0, 1), m_bStraight);
		
		m_pShape->showShape(e->pos());

		m_currentStack.push(m_pShape);
	}
	update();
}

void CPaintWidget::mouseMoveEvent(QMouseEvent *e)
{
	////////////Polygon特殊处理/////////////////  
	if (m_shapeType == Draw_Polygon)
	{
		Polygon *tmp = dynamic_cast<Polygon *>(m_currentStack.top());
		QPoint *p = tmp->top();
		p->setX(e->x());
		p->setY(e->y());
		update();
		return;
	}
	m_pShape->set_pos(m_pShape->get_start(), e->pos(), m_bStraight);

	////////////Pen特殊处理/////////////////  
	if (m_shapeType == Draw_Pen)
	{
		m_pShape = new Line;
		m_pShape->set(m_PenColor, m_BrushColor, m_nPenSize);
		m_currentStack.push(m_pShape);
		m_pShape->set_start(e->pos());
		m_pShape->set_end(e->pos());
	}
	if ( m_shapeType == Draw_Erase)
	{
		m_pShape = new CErase;
		m_pShape->set(m_PenColor, m_BrushColor, m_nPenSize);
		m_currentStack.push(m_pShape);
		m_pShape->set_start(e->pos());
		m_pShape->set_end(e->pos());
	}
	update();
}


void CPaintWidget::mouseReleaseEvent(QMouseEvent *)
{
	////////////Pen特殊处理/////////////////  
	if (m_shapeType == Draw_Pen || m_shapeType == Draw_Erase)
	{
		CBaseShape *zero = new Pen;
		zero->set_start(QPoint(0, 0));
		zero->set_end(QPoint(0, 0));
		m_currentStack.push(zero);
	}//制造间隔点  
}

void CPaintWidget::slot_set_straight(bool c)
{
	m_bStraight = c;
}

///////////////////SLOT/////////////  
void CPaintWidget::slot_set_penColor(QColor c)
{
	m_PenColor = c;
}
void CPaintWidget::slot_set_brushColor(QColor c)
{
	int tmp;
	int a;
	m_BrushColor.getRgb(&tmp, &tmp, &tmp, &a);
	m_BrushColor = c;
	m_BrushColor.setAlpha(a);

}

void CPaintWidget::slot_set_shape(DRAW_TYPE new_shape)
{
	m_shapeType = new_shape;
	if (new_shape == DRAW_TYPE::Draw_Erase)
	{
		QCursor cursor;
		//加载图片
		QPixmap pixmap(":/Image/Resources/Image/i_menu_eraser_d.png");
		//定义大小
		QSize picSize(m_nPenSize, m_nPenSize);
		//缩放图片，按比例
		QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
		//设置样式
		cursor = QCursor(scaledPixmap, -1, -1);
		//更改鼠标形状
		this->setCursor(cursor);
	}
	else
	{
		this->setCursor(Qt::ArrowCursor);
	}
}

void CPaintWidget::slot_set_penWidth(int w)
{
	m_nPenSize = w;
}

void CPaintWidget::solt_set_alpha(int a)
{
	m_BrushColor.setAlpha((100 - a) * 255 / 100);
}

////撤销  
void CPaintWidget::Undo()
{
	if (!m_currentStack.empty())
	{
		if (typeid(*m_currentStack.top()) == typeid(Pen))//运行期类型识别  
		{

			m_redoStack.push(m_currentStack.top());
			m_currentStack.pop();

			while (1) //寻找临界点  
			{
				if (m_currentStack.top()->get_start() == QPoint(0, 0) && m_currentStack.top()->get_end() == QPoint(0, 0))
					break;
				m_redoStack.push(m_currentStack.top());
				m_currentStack.pop();
			}
			m_redoStack.push(m_currentStack.top());    //加入临界点  
			m_currentStack.pop();

		}
		else
		{
			CBaseShape *tmp = m_currentStack.top();
			m_currentStack.pop();
			m_redoStack.push(tmp);
		}
	}
	update();
}

///恢复  
void CPaintWidget::Redo()
{
	if (!m_redoStack.empty())
	{
		if (typeid(*m_redoStack.top()) == typeid(Pen))//运行期类型识别  
		{

			m_currentStack.push(m_redoStack.top());
			m_redoStack.pop();

			while (1) //寻找临界点  
			{
				if (m_redoStack.top()->get_start() == QPoint(0, 0) && m_redoStack.top()->get_end() == QPoint(0, 0))
					break;
				m_currentStack.push(m_redoStack.top());
				m_redoStack.pop();
			}
			m_currentStack.push(m_redoStack.top());    //加入临界点  
			m_redoStack.pop();

		}
		else
		{
			CBaseShape *tmp = m_redoStack.top();
			m_redoStack.pop();
			m_currentStack.push(tmp);
		}
	}
	update();
}

void CPaintWidget::Reset()
{
	m_BrushColor = Qt::transparent;
	m_PenColor = Qt::black;
	m_nPenSize = 1;
	m_currentStack.clear();
	m_redoStack.clear();
	m_bStopPolygon = true;
	update();
}

void CPaintWidget::open_file()
{
	QString s = QFileDialog::getOpenFileName(this, "Select A File", "/", "Paint File(*.paint)");
	if (s.isEmpty())
	{
		QMessageBox::information(this, tr("INformation"), tr("Open failed!"));
		return;
	}
	int st = 0;
	int x1, y1, x2, y2;
	int r1, r2, g1, g2, b1, b2, a1, a2;
	int width;
	Reset();
	m_savePath = s;
	QFile file(m_savePath);
	if (file.open(QFile::ReadOnly))
	{
		QTextStream cin(&file);
		while (!cin.atEnd())
		{
			st = 0;
			cin >> st;
			CBaseShape *tmp;
			if (st == 0)
				break;  //每次都会莫名其妙多读一行，，What A Fhuack  
			if (st == 5)
			{
				tmp = new Polygon;

				int size;
				cin >> size;

				for (int i = 0; i < size; ++i)
				{
					cin >> x1 >> y1;
					QPoint *p = new QPoint(x1, y1);
					dynamic_cast<Polygon*>(tmp)->push(p);
				}
				cin >> r1 >> g1 >> b1 >> a1 >> r2 >> g2 >> b2 >> a2 >> width;
				tmp->set(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);
				m_currentStack.push(tmp);

				continue;
			}
			else
				cin >> x1 >> y1 >> x2 >> y2 >> r1 >> g1 >> b1 >> a1 >> r2 >> g2 >> b2 >> a2 >> width;

			switch (st)
			{
			case 1:
				tmp = new Rect;
				break;
			case 2:
				tmp = new Line;
				break;
			case 3:
				tmp = new Pen;
				break;
			case 4:
				tmp = new Ellipse;
			}
			tmp->set_start(QPoint(x1, y1));
			tmp->set_end(QPoint(x2, y2));
			tmp->set(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);

			m_currentStack.push(tmp);
		}
	}
	file.close();
	update();
}

void CPaintWidget::save_file()
{
	if (m_currentStack.empty())
	{
		QMessageBox::information(this, tr("Information"), tr("Nothing To Be Save!"));
		return;
	}
	if (m_savePath.isEmpty())
	{
		QString s = QFileDialog::getSaveFileName(this, "Select A File", "/", "Paint File(*.paint)");
		m_savePath = s;
	}
	else
	{
		QMessageBox::information(this, tr("Information"), tr("Save Successful!"));
	}

	int r1, r2, g1, g2, b1, b2, a1, a2;
	QFile file(m_savePath);
	if (file.open(QFile::WriteOnly))
	{
		QTextStream cout(&file);
		foreach(CBaseShape *shape, m_currentStack)
		{
			if (shape->get_DrawType() == 5)
			{
				cout << "5 ";
				Polygon *p = dynamic_cast<Polygon*>(shape);
				cout << p->get_size() << " ";
				for (int i = 0; i < p->get_size(); ++i)
					cout << p->index(i)->rx() << " " << p->index(i)->ry() << " ";
			}
			else
			{
				cout << shape->get_DrawType() << " "
					<< shape->get_start().rx() << " " << shape->get_start().ry() << " "
					<< shape->get_end().rx() << " " << shape->get_end().ry() << " ";
			}

			shape->get_color().getRgb(&r1, &g1, &b1, &a1);
			shape->get_brush().getRgb(&r2, &g2, &b2, &a2);

			cout << r1 << " " << g1 << " " << b1 << " " << a1 << " "
				<< r2 << " " << g2 << " " << b2 << " " << a2 << " "
				<< shape->get_width() << endl;
		}
	}
	file.close();
}

void CPaintWidget::saveAs_file()
{
	if (m_currentStack.empty())
	{
		QMessageBox::information(this, tr("Information"), tr("Nothing To Be Save!"));
		return;
	}
	else
	{
		QString s = QFileDialog::getSaveFileName(this, "Select A File", "/", "Paint File(*.paint)");
		m_savePath = s;
	}
	save_file();
}