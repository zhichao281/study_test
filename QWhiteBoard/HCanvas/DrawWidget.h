#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QQueue>

#include "CanvasModelDef.h"

class CDrawWidget : public QWidget
{
	Q_OBJECT

public:
	CDrawWidget(QWidget *parent);
	~CDrawWidget();

public:
	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 初始化
	*/
	void    _Init();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 初始化UI
	*/
	void    _InitUI();


	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 绘制到图片
	*/
	QImage  _PaintDrawItem(QSize size, bool bDrawing);



	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 保存内容
	*/
	void    _SaveItem(const DRAW_ITEM &item);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 绘制内容
	*/
	void    _DrawItem(QPainter &painter, const DRAW_ITEM &item);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 绘制笔刷
	*/
	void    _DrawBrushItem(QPainter &painter, const DRAW_ITEM &item);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 绘制橡皮擦
	*/
	void    _DrawEraseItem(QImage &image, const DRAW_ITEM &item);


	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 添加点
	*/
	void    AddPoint(PEN_DATA data);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 获取绘制内容
	*/
	bool    GetDrawItem(DRAW_ITEM &data);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 撤销
	*/
	int    Undo();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 重做
	*/
	int    Redo();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 清除
	*/
	void    Clear();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 获取绘图队列信息
	*/
	void GetQueSize(int &RedoSize, int &UndoSize);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : 获取笔的总顺序
	*/
	int GetPenid();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : 设置笔的总顺序
	*/
	void SetPenid(int nPenid);


	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 设置画笔大小
	*/
	void    SetPenSize(int nSize);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 设置画笔颜色
	*/
	void    SetPenColor(const QColor &color);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 设置画笔类型
	*/
	void    SetPenType(DRAW_TYPE nType);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 设置橡皮擦大小
	*/
	void    SetEraseSize(int nSize);



	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-24
	* Describe : 清除上一次绘制轨迹
	*/
	void    ClearLastDrawItem();


	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : 重新开始
	*/
	void    ReStart();


	//继承
protected:

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : 绘制事件
	*/
	void paintEvent(QPaintEvent * e);


private:
	int                 m_nEraseSize;       //橡皮擦大小
	int                 m_nPenSize;         //笔迹大小
	QColor              m_penColor;         //笔迹颜色

	QVector<PEN_DATA>   m_vectAllData;      //所有坐标信息
	QVector<QPoint>     m_vectDrawData;     //绘制坐标信息
	int                 m_nPenId;           //笔迹ID顺序
	bool                m_bFlagDrawing;     //正在绘制标识
	bool                m_bFlagClear;       //清除标识
	PEN_STATE           m_penState;         //点阵笔状态
	QColor              m_bkColor;          //背景颜色

	QQueue<DRAW_ITEM>   m_queDrawItem;      //保存绘制

	QQueue<DRAW_ITEM>   m_queRedoItem;      //保存重做

	DRAW_ITEM           m_drawItem;         //正在绘制
};

#endif // DRAWWIDGET_H
