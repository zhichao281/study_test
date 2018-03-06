#include "HCanvas.h"
#include <QPainter>
#include <QDateTime>
HCanvas::HCanvas(QWidget *parent) : QWidget(parent)
{

	this->setStyleSheet("background-color: rgb(255, 255, 0);");
	setAcceptDrops(true);
	this->setFixedSize(792, 600);
	_Init();
	m_drawWidget.reset(new CDrawWidget(this));
	m_drawWidget->setGeometry(0, 0, this->width(), this->height());

	//m_drawWidget->setGeometry(0, 0,0,0);
	
	m_bskWidget.reset(new CBkImageWidget(nullptr));
	//m_bskWidget->setGeometry(0, 0, this->width(), this->height());
	m_bskWidget->setGeometry(0, 0, 0, 0);

}

/**
* @brief 设置背景图片
* @param strFile   图片路径
* @return
*/
bool HCanvas::SetBkImage(QString strFile)
{
	m_bskWidget->SetBkImage(strFile);
	return true;
}


/**
* @brief 获取笔的顺序大小
*/
int HCanvas::GetPenid()
{
	return m_nPenId;
}

/**
* @brief 设置笔的总顺序
*/

void HCanvas::SetPenid(int nPenid)
{
	m_nPenId = nPenid;
}

/**
* @brief 添加图片
* @param strfile     图片路径
*/
int  HCanvas::addPic(QString strFile, bool bRecord)
{
	ImageWidget *Icon = new ImageWidget(this);
	strFile = CoptToTempFile(strFile);
	QPixmap pix;
	bool bRes = pix.load(strFile);
	if (!bRes)
		return 0;

	int nPixWidth = pix.width();
	int nPixHeight = pix.height();
	Icon->setPixmap(pix);
	Icon->move(this->width() / 2 - nPixWidth / 2, this->height() / 2 - nPixHeight / 2);
	Icon->setSize(nPixWidth, nPixHeight);
	Icon->show();
	Icon->setAttribute(Qt::WA_DeleteOnClose);
	if (bRecord)
		m_nPenId++;
	Icon->SetImageInfo(m_nPenId);
	m_drawWidget->raise();
	return m_nPenId;
}
/**
* @brief 添加图片
* @param strfile     图片路径
*/
int HCanvas::addPic(QImage image, bool bRecord)
{
	QPixmap pix = QPixmap::fromImage(image);
	int nPixWidth = pix.width();
	int nPixHeight = pix.height();
	ImageWidget *Icon = new ImageWidget(this);
	Icon->setPixmap(pix);
	Icon->move(this->width() / 2 - nPixWidth / 2, this->height() / 2 - nPixHeight / 2);
	Icon->setSize(nPixWidth, nPixHeight);
	Icon->show();
	Icon->setAttribute(Qt::WA_DeleteOnClose);
	if (bRecord)
		m_nPenId++;
	Icon->SetImageInfo(m_nPenId);
	return m_nPenId;
}


/**
* @brief 设置橡皮擦大小
* @param nSize     大小
*/
void HCanvas::SetEraseSize(int nSize)
{
	m_drawWidget->SetEraseSize(nSize);
}

/**
* @brief 设置画笔大小
* @param nSize     大小
*/
void HCanvas::SetPenSize(int nSize)
{
	m_drawWidget->SetPenSize(nSize);
}

/**
* @brief 设置画笔颜色
* @param color     颜色
*/
void HCanvas::SetPenColor(const QColor &color)
{
	m_drawWidget->SetPenColor(color);
}

/**
* @brief 设置画笔类型
* @param nType     类型
*/
void HCanvas::SetPenType(DRAW_TYPE nType)
{
	m_drawWidget->SetPenType(nType);
}

/**
* @brief 添加点
* @param data      点数据
*/
void HCanvas::AddPoint(PEN_DATA data)
{
	m_drawWidget->AddPoint(data);

}

void HCanvas::ClearLastDrawItem()
{
	m_drawWidget->ClearLastDrawItem();
}

/**
* @brief 获取绘制内容
* @param data      绘制内容
* @return
*/
bool HCanvas::GetDrawItem(DRAW_ITEM &data)
{
	m_drawWidget->GetDrawItem(data);
	return true;
}

/**
* @brief 撤销
*/
int HCanvas::Undo()
{
	return m_drawWidget->Undo();
}

/**
* @brief 重做
*/
int HCanvas::Redo()
{
	return m_drawWidget->Redo();
}

/**
* @brief 清除
*/
void HCanvas::Clear()
{
	m_drawWidget->Clear();
}

/**
* @brief 重新开始
*/
void HCanvas::ReStart()
{
	m_drawWidget->ReStart();
	m_nPenId = 0;
	QList<ImageWidget *> allImage = findChildren<ImageWidget *>();
	{
		if (allImage.size()>0)
		{
			foreach(ImageWidget * image, allImage)
			{
				image->close();
				image->deleteLater();
			}
		}
	}
}

/**
* @brief 获取画布内容
* @param pixmap        图片
*/
void HCanvas::GetImage(QPixmap &pixmap)
{
	pixmap = grab();
}

/**
* @brief 初始化
*/
void HCanvas::_Init()
{

	dir.setAutoRemove(true);
	if (dir.isValid())
	{
		m_TempDir = dir.path();//returns the unique directory path

	}
	createAction();

	createMenu();
	//初始化右键事件
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(On_Slot_ContextMenu(QPoint)));

	_InitUI();
}

/**
* @brief 初始化UI
*/
void HCanvas::_InitUI()
{

}

/**
* @brief 计算矩形
* @param rt        矩形
* @param posBegin  开始点
* @param posEnd    结束点
*/
void HCanvas::_CalcRect(QRect &rt, QPoint posBegin, QPoint posEnd)
{
	//计算Left和Right
	if (posBegin.x() > posEnd.x())
	{
		rt.setLeft(posEnd.x());
		rt.setRight(posBegin.x());
	}
	else
	{
		rt.setLeft(posBegin.x());
		rt.setRight(posEnd.x());
	}

	//计算Top和Bottom
	if (posBegin.y() > posEnd.y())
	{
		rt.setTop(posEnd.y());
		rt.setBottom(posBegin.y());
	}
	else
	{
		rt.setTop(posBegin.y());
		rt.setBottom(posEnd.y());
	}
}




/**
* @brief 鼠标点击事件
* @param event
*/
void HCanvas::mousePressEvent(QMouseEvent *event)
{
	m_startPnt = event->pos();
	m_endPnt = event->pos();
	m_bPressed = true;
	//添加笔落下动作
	PEN_DATA data;
	data.nPenState = PS_DOWN;
	data.nPenType = (DRAW_TYPE)1;
	AddPoint(data);
	

}

/**
* @brief 鼠标移动事件
* @param event
*/
void HCanvas::mouseMoveEvent(QMouseEvent *e)
{
	if (m_bPressed)
	{
		m_endPnt = e->pos();
		QPoint retPos;
		int nX = m_endPnt.x();
		int nY = m_endPnt.y();
		retPos.setX(nX);
		retPos.setY(nY);
		PEN_DATA data;
		data.nPenType = (DRAW_TYPE)1;
		data.nSize = 1;
		data.nPenState = PS_WRITE;
		data.color = Qt::red;
		data.pos = retPos;
		AddPoint(data);
		m_startPnt = m_endPnt;
	}
}

/**
* @brief 鼠标释放事件
* @param event
*/
void HCanvas::mouseReleaseEvent(QMouseEvent *e)
{
	m_startPnt = e->pos();

	m_bPressed = false;

	//添加笔抬起动作
	PEN_DATA data;
	data.nPenState = PS_UP;
	data.nPenType = (DRAW_TYPE)1;
	AddPoint(data);	
	DRAW_ITEM item;
	GetDrawItem(item);
}







void HCanvas::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	//m_drawWidget->resize(this->size());
	

}


/**
* @brief 创建右键菜单
*/
void HCanvas::On_Slot_ContextMenu(QPoint pos)
{
	m_MenuImage = static_cast<ImageWidget*>(childAt(pos));
	if (!m_MenuImage)
		return;
	m_menu->exec(this->mapToGlobal(pos));
}

/**
* @brief 创建右键菜单
*/
void HCanvas::createMenu()
{
	m_menu = new QMenu(this);
	m_menu->setStyleSheet("QMenu{background-color: rgb(255, 255, 255); border: 1px solid white;}\
						                            QMenu::item:selected{\
													                              background-color: #2dabf9;}/*这一句是设置菜单项鼠标经过选中的样式*/\
																				                            QMenu::item:!enabled{color:#757575;}"\
																											);
	m_menu->addAction(m_copyAction);
	// m_menu->addAction(m_pasteAction);
	m_menu->addAction(m_RotateAction);
	m_menu->addAction(m_clearAction);
}


/**
* @brief 创建右键菜单动作指令
*/
void HCanvas::createAction()
{
	m_copyAction = new QAction(QStringLiteral("复制"), this);
	connect(m_copyAction, &QAction::triggered, this, [=]()
	{
		if (m_MenuImage)
		{
			m_MenuImage->SetEditState(false);
			qreal angle = m_MenuImage->GetRotate();
			QPixmap pix = m_MenuImage->getPixmap();
			QMatrix leftmatrix;
			leftmatrix.rotate(angle);
			pix = pix.transformed(leftmatrix, Qt::SmoothTransformation);
			ImageWidget *Icon = new ImageWidget(this);
			Icon->setPixmap(pix);
			Icon->move(m_MenuImage->pos().x() + 20, m_MenuImage->pos().y() + 20);
			Icon->setSize(m_MenuImage->width(), m_MenuImage->height());
			Icon->show();
			Icon->setAttribute(Qt::WA_DeleteOnClose);
			if (m_nPenId>0)
				m_nPenId++;
			Icon->SetImageInfo(m_nPenId);
		}
	});

	m_RotateAction = new QAction(QStringLiteral("旋转"), this);
	connect(m_RotateAction, &QAction::triggered, this, [=]()
	{
		if (m_MenuImage)
		{
			m_MenuImage->RotateImage();
		}
	});

	m_clearAction = new QAction(QStringLiteral("删除"), this);
	connect(m_clearAction, &QAction::triggered, this, [=]()
	{
		if (m_MenuImage)
		{
			m_MenuImage->close();
			m_MenuImage->deleteLater();
		}
	});
}

void HCanvas::GetQueSize(int &RedoSize, int &UndoSize)
{
	m_drawWidget->GetQueSize(RedoSize, UndoSize);
}

void HCanvas::ClearDrawData()
{
	m_nPenId = 0;

}

QString HCanvas::GetFileHead(QString strPath)
{
	QString strFomat = "bmp";
	QFile tmpfile(strPath);
	bool bOpen = tmpfile.open(QIODevice::ReadOnly);
	if (bOpen)
	{
		QByteArray bytes = tmpfile.readAll();
		tmpfile.close();
		QByteArray byteGifhead = bytes.mid(0, 3);
		QString strHead = byteGifhead.toHex();
		if (QString::compare("GIF", QString(byteGifhead)) == 0)
		{
			strFomat = "gif";
		}
		QString strJpgHead = "ffd8ff";
		if (QString::compare(strJpgHead, strHead.toLower()) == 0)
		{
			strFomat = "jpg";
		}
		QByteArray bytepnghead = bytes.mid(1, 3);
		QString strPnghead = QString(bytepnghead).toUpper();
		if (QString("PNG") == strPnghead)
		{
			strFomat = "png";
		}
	}
	return strFomat;
}

QString HCanvas::CoptToTempFile(QString sourceDir)
{
	QFileInfo info(sourceDir);
	//文件名+后缀名
	QString file_name = info.baseName();
	QString strFomat = "png";
	strFomat = GetFileHead(sourceDir);

	QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
	QString str = time.toString("hhmmsszzz"); //设置显示格式
	QString strDest = QString("%1/%2_%3.%4").arg(m_TempDir).arg(file_name).arg(str).arg(strFomat);
	QFile::copy(sourceDir, strDest);
	return strDest;

}

