#include "DrawWidget.h"
#include <QPainter>

CDrawWidget::CDrawWidget(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowOpacity(1);
	
	this->setMouseTracking(true);
	_Init();

	
}

CDrawWidget::~CDrawWidget()
{

}
/**
* @brief 初始化
*/
void CDrawWidget::_Init()
{
	m_nEraseSize = 5;
	m_nPenSize = 2;
	m_bFlagDrawing = false;
	m_bFlagClear = false;
	m_nPenId = 0;

	_InitUI();
}

/**
* @brief 初始化UI
*/
void CDrawWidget::_InitUI()
{

}



/**
* @brief 绘制事件
*/
void CDrawWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	QRect rt = rect();
	//painter.drawRect(rt);
	QImage image = _PaintDrawItem(rt.size(), true);
	painter.drawImage(rt, image);
	QWidget::paintEvent(event);
	return;

}

/**
* @brief 绘制到图片
* @param size      大小
* @param bDrawing  是否正在绘制
* @return
*/
QImage CDrawWidget::_PaintDrawItem(QSize size, bool bDrawing)
{
	QImage image(size, QImage::Format_ARGB32);
	image.fill(qRgba(0, 0xFF, 0xFF, 0));

	//绘制旧内容
	QPainter painter(&image);
	for (int i = 0; i < m_queDrawItem.size(); ++i)
	{
		DRAW_ITEM item = m_queDrawItem[i];
		if (item.penData.nPenType == DT_ERASE)
			_DrawEraseItem(image, item);
		else
			_DrawItem(painter, item);
	}

	//绘制新内容
	if (bDrawing)
	{
		if (m_drawItem.penData.nPenState == PS_WRITE)
		{
			if (m_drawItem.penData.nPenType == DT_ERASE)
				_DrawEraseItem(image, m_drawItem);
			else
				_DrawItem(painter, m_drawItem);
		}
	}
	return image;

	//返回图片:背景图片+绘制轨迹
	QImage retImage(size, QImage::Format_ARGB32);
	retImage.fill(Qt::white);

	//绘制轨迹
	QPainter retPainter(&retImage);
	retPainter.drawImage(0, 0, image);	


	return retImage;
}


/**
* @brief 保存内容
* @param item      绘制内容
*/
void CDrawWidget::_SaveItem(const DRAW_ITEM &item)
{
	if (item.penData.nPenType == DT_ERASE &&
		m_queDrawItem.isEmpty())
	{
		return;
	}
	m_queDrawItem.push_back(item);
	m_queRedoItem.clear();
	m_bFlagClear = false;
}

/**
* @brief 绘制内容
* @param painter   画笔
* @param item      绘制内容
*/
void CDrawWidget::_DrawItem(QPainter &painter, const DRAW_ITEM &item)
{
	QPen pen(item.penData.color, item.penData.nSize);
	Qt::PenCapStyle      PenCapstyle = Qt::RoundCap;     //线的端点样式
	if (item.penData.nSize == 2 || item.penData.nSize == 6)
		PenCapstyle = Qt::RoundCap;
	else
	{
		PenCapstyle = Qt::SquareCap;
	}
	pen.setCapStyle(PenCapstyle);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);
	painter.setBrush(Qt::transparent);

	switch (item.penData.nPenType)
	{
	case DT_TRACE:
		_DrawBrushItem(painter, item);
		break;
	}
}

/**
* @brief 绘制笔刷
* @param painter   画笔
* @param item      绘制内容
*/
void CDrawWidget::_DrawBrushItem(QPainter &painter, const DRAW_ITEM &item)
{
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPolyline(item.vectPath);
}

/**
* @brief 绘制橡皮擦
* @param image     原始图片
* @param item      绘制内容
*/
void CDrawWidget::_DrawEraseItem(QImage &image, const DRAW_ITEM &item)
{
	//绘制图片大小
	int nWidth = image.width();
	int nHeight = image.height();

	//橡皮擦图片
	QImage imageErase(nWidth, nHeight, QImage::Format_ARGB32);
	QPainter painter(&imageErase);

	//绘制擦除区域
	painter.setPen(QPen(QColor(0xFF, 0xFF, 0xFF, 0xFF), item.penData.nSize));
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPolyline(item.vectPath);

	//合成图片
	int nCnt = nWidth * nHeight;
	quint32 *pBits = (quint32*)image.bits();
	quint32 *pBitsErase = (quint32*)imageErase.bits();
	for (int i = 0; i < nCnt; ++i)
	{
		if (pBitsErase[i] == 0xFFFFFFFF && (pBits[i] < 0 || pBits[i] > 255))
		{
			pBits[i] = 0;
		}
	}
}

/**
* @brief 添加点
* @param data      点数据
*/
void CDrawWidget::AddPoint(PEN_DATA data)
{
	if (data.nPenType == DT_NULL)
		return;


	if (data.nPenType == DT_TRACE ||data.nPenType == DT_ERASE)
	{
		//过滤起始点和结束点
		if (data.nPenState != PS_DOWN && data.nPenState != PS_UP)
		{
			//忽略跟上一个点相同的点
			QVector<QPoint> vectPos = m_drawItem.vectPath;
			if (!vectPos.isEmpty())
			{
				if (vectPos.last() == data.pos)
					return;
			}

			m_drawItem.penData = data;
			m_drawItem.vectTimestamp.push_back(data.nTimestamp);
			m_drawItem.vectPath.push_back(data.pos);
		

		}
		else
		{
			m_drawItem.penData.nPenState = data.nPenState;
			m_drawItem.penData.nPenType = data.nPenType;

		}
	}
	update();
}

/**
* @brief 获取绘制内容
* @param data      绘制内容
* @return
*/
bool CDrawWidget::GetDrawItem(DRAW_ITEM &data)
{
	data = m_drawItem;

	//保存起始点和结束点
	if (!data.vectPath.isEmpty())
	{
		data.posBegin = data.vectPath.first();
		data.posEnd = data.vectPath.last();
	}
	int nType = data.penData.nPenType;
	if (nType != DT_NULL)
	{

		if (data.penData.nPenType == DT_ERASE &&
			m_queDrawItem.isEmpty() )
		{

		}
		else
		{
			if (data.vectPath.size() > 0)
			{
				m_nPenId++;
				data.penData.nPenId = m_nPenId;
				data.penData.nChangeId = 0;
				_SaveItem(data);
			}
		}

	}

	if (data.penData.nPenState == PS_UP)
	{
		m_drawItem.Init();
	}
	return true;
}


/**
* @brief 撤销
*/
int CDrawWidget::Undo()
{
	int res = 0;
	DRAW_ITEM      drawItem;
	if (!m_queDrawItem.isEmpty())
	{
		if (!m_bFlagClear)
		{
			drawItem = m_queDrawItem.back();
			res = drawItem.penData.nPenId;
			m_queRedoItem.push_back(drawItem);
			m_queDrawItem.pop_back();
			m_nPenId++;
		}
		else
		{
			m_queRedoItem = m_queDrawItem;
			m_queDrawItem.clear();
		}
	}


	update();
	return res;

}

/**
* @brief 重做
*/
int CDrawWidget::Redo()
{
	int res = 0;
	DRAW_ITEM      drawItem;
	if (!m_queRedoItem.isEmpty())
	{
		if (!m_bFlagClear)
		{
			drawItem = m_queRedoItem.back();
			res = drawItem.penData.nPenId;
			m_queDrawItem.push_back(m_queRedoItem.back());
			m_queRedoItem.pop_back();
			m_nPenId++;
		}
		else
		{
			m_queDrawItem = m_queRedoItem;
			m_queRedoItem.clear();
		}
	}
	update();
	return res;
}

/**
* @brief 清除
*/
void CDrawWidget::Clear()
{

	m_bFlagClear = true;
	m_queRedoItem = m_queDrawItem;
	m_queDrawItem.clear();
	m_nPenId++;

}
void CDrawWidget::GetQueSize(int &RedoSize, int &UndoSize)
{
	RedoSize = m_queRedoItem.size();
	UndoSize = m_queDrawItem.size();
}

/**
* @brief 设置橡皮擦大小
* @param nSize     大小
*/
void CDrawWidget::SetEraseSize(int nSize)
{
	m_nEraseSize = nSize;
}

/**
* @brief 设置画笔大小
* @param nSize     大小
*/
void CDrawWidget::SetPenSize(int nSize)
{
	m_nPenSize = nSize;
}

/**
* @brief 设置画笔颜色
* @param color     颜色
*/
void CDrawWidget::SetPenColor(const QColor &color)
{
	m_penColor = color;
}

/**
* @brief 设置画笔类型
* @param nType     类型
*/
void CDrawWidget::SetPenType(DRAW_TYPE nType)
{
	m_drawItem.penData.nPenType = nType;
}


void CDrawWidget::ClearLastDrawItem()
{
	m_drawItem.Init();
}

/**
* @brief 重新开始
*/
void CDrawWidget::ReStart()
{
	m_bFlagClear = true;
	m_queRedoItem.clear();
	m_queDrawItem.clear();
	m_nPenId = 0;
}