#include "mainwindows.h"  
#include <QPixmap>
#include <QPalette>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{


	

	///////形状选择框架///////  
	QToolBar *shapeBar = this->addToolBar("Shape");
	QActionGroup *shapeGroup = new QActionGroup(shapeBar);

	QAction *act_rect = new QAction( "Rect", shapeBar);
	act_rect->setCheckable(true);
	act_rect->setChecked(true);
	shapeGroup->addAction(act_rect);
	shapeBar->addAction(act_rect);

	QAction *act_line = new QAction( "Line", shapeBar);
	act_line->setCheckable(true);
	shapeGroup->addAction(act_line);
	shapeBar->addAction(act_line);

	QAction *act_pen = new QAction( "Pen", shapeBar);
	act_pen->setCheckable(true);
	shapeGroup->addAction(act_pen);
	shapeBar->addAction(act_pen);

	QAction *act_erase = new QAction("Erase", shapeBar);
	act_erase->setCheckable(true);
	shapeGroup->addAction(act_erase);
	shapeBar->addAction(act_erase);

	QAction *act_ellipse = new QAction( "Ellipse", shapeBar);
	act_ellipse->setCheckable(true);
	shapeGroup->addAction(act_ellipse);
	shapeBar->addAction(act_ellipse);

	QAction *act_polygon = new QAction( "Polygon", shapeBar);
	act_polygon->setCheckable(true);
	shapeGroup->addAction(act_polygon);
	shapeBar->addAction(act_polygon);

	QAction *act_Text = new QAction("Text", shapeBar);
	act_Text->setCheckable(true);
	shapeGroup->addAction(act_Text);
	shapeBar->addAction(act_Text);

	QAction *act_Arrow = new QAction("Arrow", shapeBar);
	act_Arrow->setCheckable(true);
	shapeGroup->addAction(act_Arrow);
	shapeBar->addAction(act_Arrow);

	QAction *act_Image = new QAction("Image", shapeBar);
	act_Image->setCheckable(true);
	shapeGroup->addAction(act_Image);
	shapeBar->addAction(act_Image);

	////////操作选择框架/////////////  
	QToolBar *operatorBar = this->addToolBar("Operator");
	QActionGroup *operatorGroup = new QActionGroup(operatorBar);
	QAction *Undo = new QAction("Undo", operatorBar);
	Undo->setShortcut(tr("Ctrl+Z"));
	operatorGroup->addAction(Undo);
	operatorBar->addAction(Undo);

	QAction *Redo = new QAction( "Redo", operatorBar);
	Redo->setShortcut(tr("Ctrl+Y"));
	operatorGroup->addAction(Redo);
	operatorBar->addAction(Redo);

	QAction *Reset = new QAction("Reset", operatorBar);
	Reset->setShortcut(tr("Ctrl+N"));
	operatorGroup->addAction(Reset);
	operatorBar->addAction(Reset);

	widthDial = new QDial(operatorBar);
	widthDial->setRange(1, 20);
	operatorBar->addWidget(widthDial);
	widthLabel = new QLabel("Size: 1", operatorBar);
	operatorBar->addWidget(widthLabel);

	alphaDial = new QDial(operatorBar);
	alphaDial->setRange(0, 100);
	alphaDial->setValue(100);
	operatorBar->addWidget(alphaDial);
	alphaLabel = new QLabel("Alpha: 100%", operatorBar);
	operatorBar->addWidget(alphaLabel);

	////////////菜单区域////////////////  
	QMenu *file = menuBar()->addMenu(tr("&File"));
	QAction *newFile = new QAction(tr("New"), file);
	newFile->setShortcut(tr("Ctrl+N"));
	file->addAction(newFile);
	QAction *openFile = new QAction( tr("Open"), file);
	openFile->setShortcut(tr("Ctrl+O"));
	file->addAction(openFile);
	QAction *saveFile = new QAction( tr("Save"), file);
	saveFile->setShortcut(tr("Ctrl+S"));
	file->addAction(saveFile);
	QAction *saveAsFile = new QAction( tr("Save As"), file);
	saveAsFile->setShortcut(tr("Ctrl+Alt+S"));
	file->addAction(saveAsFile);
	QAction *quit = new QAction(tr("Quit"), file);
	quit->setShortcut(tr("Ctrl+Q"));
	file->addAction(quit);

	QMenu *change = menuBar()->addMenu(tr("&Change"));
	QAction *changeColor = new QAction(tr("Color"), change);
	changeColor->setShortcut(tr("Ctrl+C"));
	change->addAction(changeColor);
	QAction *changeBrush = new QAction( tr("Brush"), change);
	changeBrush->setShortcut(tr("Ctrl+B"));
	change->addAction(changeBrush);
	QAction *changeWidth = new QAction( tr("Width"), change);
	changeWidth->setShortcut(tr("Ctrl+W"));
	change->addAction(changeWidth);

	////////////paint定义////////////  
	 m_pCanvas  = new HCanvas(this);
	setCentralWidget(m_pCanvas);
	//设置初始颜色及大小
	m_pToolBarWidget = new CToolBarWidget(m_pCanvas);
	connect(m_pToolBarWidget, SIGNAL(Sig_ChangePenStates()), this, SLOT(On_Slot_ChangePenStates()));

	//清屏按钮信号槽绑定
	connect(m_pToolBarWidget, SIGNAL(Sig_EraseBtnClicked()), this, SLOT(On_Slot_EraseBtnClicked()));

	m_pToolBarWidget->show();
	m_pToolBarWidget->raise();
	
														 													 ////////工具栏信号槽//////////////////  
	QObject::connect(act_rect, SIGNAL(triggered()), this, SLOT(draw_rect()));
	QObject::connect(act_line, SIGNAL(triggered()), this, SLOT(draw_line()));
	QObject::connect(act_pen, SIGNAL(triggered()), this, SLOT(draw_pen()));
	QObject::connect(act_Text, SIGNAL(triggered()), this, SLOT(draw_text()));
	QObject::connect(act_Arrow, SIGNAL(triggered()), this, SLOT(draw_Arrow()));
	QObject::connect(act_Image, SIGNAL(triggered()), this, SLOT(draw_Image()));

	
	QObject::connect(act_erase, SIGNAL(triggered()), this, SLOT(draw_erase()));
	QObject::connect(act_polygon, SIGNAL(triggered()), this, SLOT(draw_polygon()));
	QObject::connect(act_ellipse, SIGNAL(triggered()), this, SLOT(draw_ellipse()));
	QObject::connect(Undo, SIGNAL(triggered()), m_pCanvas, SIGNAL(sig_Undo()));
	QObject::connect(Redo, SIGNAL(triggered()), m_pCanvas, SIGNAL(sig_Redo()));
	QObject::connect(Reset, SIGNAL(triggered()), m_pCanvas, SIGNAL(sig_Reset()));
	QObject::connect(Reset, SIGNAL(triggered()), this, SLOT(reset_dial()));
	QObject::connect(widthDial, SIGNAL(valueChanged(int)), m_pCanvas, SIGNAL(sig_set_penSize(int)));
	QObject::connect(widthDial, SIGNAL(valueChanged(int)), this, SLOT(change_widthLabel(int)));
	QObject::connect(alphaDial, SIGNAL(valueChanged(int)), m_pCanvas, SIGNAL(sig_set_brushAlpha(int)));
	QObject::connect(alphaDial, SIGNAL(valueChanged(int)), this, SLOT(change_alphaLabel(int)));

	////////菜单栏信号槽//////////////////  
	QObject::connect(newFile, SIGNAL(triggered()), m_pCanvas, SIGNAL(sig_Reset()));
	//QObject::connect(openFile, SIGNAL(triggered()), paint, SLOT(open_file()));
	//QObject::connect(saveFile, SIGNAL(triggered()), paint, SLOT(save_file()));
	//QObject::connect(saveAsFile, SIGNAL(triggered()), paint, SLOT(saveAs_file()));
	QObject::connect(quit, SIGNAL(triggered()), this, SLOT(close()));
	QObject::connect(changeColor, SIGNAL(triggered()), this, SLOT(color_SLOT()));
	QObject::connect(changeBrush, SIGNAL(triggered()), this, SLOT(brush_SLOT()));
	QObject::connect(changeWidth, SIGNAL(triggered()), this, SLOT(width_SLOT()));

	/////////Paint交互信号槽///////////////////  
	QObject::connect(this, SIGNAL(select_shape(DRAW_TYPE)), m_pCanvas, SIGNAL(sig_set_shape(DRAW_TYPE)));
	QObject::connect(this, SIGNAL(color_change(QColor)), m_pCanvas, SIGNAL(sig_set_penColor(QColor)));
	QObject::connect(this, SIGNAL(brush_change(QColor)), m_pCanvas, SIGNAL(sig_set_brushColor(QColor)));
	QObject::connect(this, SIGNAL(width_change(int)), m_pCanvas, SIGNAL(sig_set_penSize(int)));
	QObject::connect(this, SIGNAL(change_straight(bool)), m_pCanvas, SIGNAL(sig_change_straight(bool)));
}

///////信息发射///////////////  
void MainWindow::keyPressEvent(QKeyEvent *k)
{
	if (k->modifiers() == Qt::ShiftModifier)
	{
		emit change_straight(true);
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *k)
{
	if (k->key() == Qt::Key_Shift)
	{
		emit change_straight(false);
	}
}

void MainWindow::color_SLOT()
{
	QColor c = QColorDialog::getColor(Qt::black);
	emit color_change(c);
}

void MainWindow::brush_SLOT()
{
	QColor c = QColorDialog::getColor(Qt::transparent);
	emit brush_change(c);
}

void MainWindow::width_SLOT()
{
	int c = QInputDialog::getInt(this, tr("Width Set"), tr("Enter the Width"), true, 1, 20, 1);
	emit width_change(c);
}

void MainWindow::draw_rect()
{
	emit select_shape(Draw_Rect);
}
void MainWindow::draw_line()
{
	emit select_shape(Draw_Line);
}
void MainWindow::draw_Image()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png)"));
	if (path.length() == 0)
	{
		QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
	}


	else 
	{
		m_pCanvas->setBackgroundImage(path);
		//QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
	}

}
void MainWindow::draw_pen()
{
	emit select_shape(Draw_Pen);
}
void MainWindow::draw_erase()
{
	emit select_shape(Draw_Erase);
}


void MainWindow::draw_polygon()
{
	emit select_shape(Draw_Polygon);
}
void MainWindow::draw_ellipse()
{
	emit select_shape(Draw_Ellipse);
}
void MainWindow::draw_text()
{
	emit select_shape(Draw_Text);
	
}
void MainWindow::draw_Arrow()
{
	emit select_shape(Draw_Arrow);

}



/**
* @brief 画笔的样式改变
*/
void MainWindow::On_Slot_ChangePenStates()
{
	int nPenType, nPenSize;
	QColor pPenColor;
	Qt::PenCapStyle PenCapstyle;
	m_pToolBarWidget->GetPenData(nPenType, nPenSize, pPenColor, PenCapstyle);
	
	emit select_shape((DRAW_TYPE)nPenType);

	emit m_pCanvas->sig_set_penColor(pPenColor);

	if ((DRAW_TYPE)nPenType == DRAW_TYPE::Draw_Erase)
	{
		emit m_pCanvas->sig_set_EraseSize(nPenSize);
	}
	else
	{
		emit m_pCanvas->sig_set_penSize(nPenSize);
	}


	

}





///////////////////槽函数////////////////  
void MainWindow::change_widthLabel(int w)
{
	widthLabel->setText("Size: " + QString::number(w));
}

void MainWindow::change_alphaLabel(int w)
{
	alphaLabel->setText("Alpha: " + QString::number(w) + "%");
}

void MainWindow::reset_dial()
{
	widthDial->setValue(1);
	alphaDial->setValue(100);
	widthLabel->setText("Size: 1");
	alphaLabel->setText("Alpha: 100%");
}

//////////其他//////////  
MainWindow::~MainWindow()
{

}

QSize MainWindow::sizeHint() const
{
	return QSize(1024, 768);
}