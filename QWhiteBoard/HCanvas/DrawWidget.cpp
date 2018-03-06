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
* @brief ��ʼ��
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
* @brief ��ʼ��UI
*/
void CDrawWidget::_InitUI()
{

}



/**
* @brief �����¼�
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
* @brief ���Ƶ�ͼƬ
* @param size      ��С
* @param bDrawing  �Ƿ����ڻ���
* @return
*/
QImage CDrawWidget::_PaintDrawItem(QSize size, bool bDrawing)
{
	QImage image(size, QImage::Format_ARGB32);
	image.fill(qRgba(0, 0xFF, 0xFF, 0));

	//���ƾ�����
	QPainter painter(&image);
	for (int i = 0; i < m_queDrawItem.size(); ++i)
	{
		DRAW_ITEM item = m_queDrawItem[i];
		if (item.penData.nPenType == DT_ERASE)
			_DrawEraseItem(image, item);
		else
			_DrawItem(painter, item);
	}

	//����������
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

	//����ͼƬ:����ͼƬ+���ƹ켣
	QImage retImage(size, QImage::Format_ARGB32);
	retImage.fill(Qt::white);

	//���ƹ켣
	QPainter retPainter(&retImage);
	retPainter.drawImage(0, 0, image);	


	return retImage;
}


/**
* @brief ��������
* @param item      ��������
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
* @brief ��������
* @param painter   ����
* @param item      ��������
*/
void CDrawWidget::_DrawItem(QPainter &painter, const DRAW_ITEM &item)
{
	QPen pen(item.penData.color, item.penData.nSize);
	Qt::PenCapStyle      PenCapstyle = Qt::RoundCap;     //�ߵĶ˵���ʽ
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
* @brief ���Ʊ�ˢ
* @param painter   ����
* @param item      ��������
*/
void CDrawWidget::_DrawBrushItem(QPainter &painter, const DRAW_ITEM &item)
{
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPolyline(item.vectPath);
}

/**
* @brief ������Ƥ��
* @param image     ԭʼͼƬ
* @param item      ��������
*/
void CDrawWidget::_DrawEraseItem(QImage &image, const DRAW_ITEM &item)
{
	//����ͼƬ��С
	int nWidth = image.width();
	int nHeight = image.height();

	//��Ƥ��ͼƬ
	QImage imageErase(nWidth, nHeight, QImage::Format_ARGB32);
	QPainter painter(&imageErase);

	//���Ʋ�������
	painter.setPen(QPen(QColor(0xFF, 0xFF, 0xFF, 0xFF), item.penData.nSize));
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPolyline(item.vectPath);

	//�ϳ�ͼƬ
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
* @brief ��ӵ�
* @param data      ������
*/
void CDrawWidget::AddPoint(PEN_DATA data)
{
	if (data.nPenType == DT_NULL)
		return;


	if (data.nPenType == DT_TRACE ||data.nPenType == DT_ERASE)
	{
		//������ʼ��ͽ�����
		if (data.nPenState != PS_DOWN && data.nPenState != PS_UP)
		{
			//���Ը���һ������ͬ�ĵ�
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
* @brief ��ȡ��������
* @param data      ��������
* @return
*/
bool CDrawWidget::GetDrawItem(DRAW_ITEM &data)
{
	data = m_drawItem;

	//������ʼ��ͽ�����
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
* @brief ����
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
* @brief ����
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
* @brief ���
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
* @brief ������Ƥ����С
* @param nSize     ��С
*/
void CDrawWidget::SetEraseSize(int nSize)
{
	m_nEraseSize = nSize;
}

/**
* @brief ���û��ʴ�С
* @param nSize     ��С
*/
void CDrawWidget::SetPenSize(int nSize)
{
	m_nPenSize = nSize;
}

/**
* @brief ���û�����ɫ
* @param color     ��ɫ
*/
void CDrawWidget::SetPenColor(const QColor &color)
{
	m_penColor = color;
}

/**
* @brief ���û�������
* @param nType     ����
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
* @brief ���¿�ʼ
*/
void CDrawWidget::ReStart()
{
	m_bFlagClear = true;
	m_queRedoItem.clear();
	m_queDrawItem.clear();
	m_nPenId = 0;
}