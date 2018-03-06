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
	* Describe : ��ʼ��
	*/
	void    _Init();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ��ʼ��UI
	*/
	void    _InitUI();


	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���Ƶ�ͼƬ
	*/
	QImage  _PaintDrawItem(QSize size, bool bDrawing);



	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ��������
	*/
	void    _SaveItem(const DRAW_ITEM &item);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ��������
	*/
	void    _DrawItem(QPainter &painter, const DRAW_ITEM &item);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���Ʊ�ˢ
	*/
	void    _DrawBrushItem(QPainter &painter, const DRAW_ITEM &item);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ������Ƥ��
	*/
	void    _DrawEraseItem(QImage &image, const DRAW_ITEM &item);


	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ��ӵ�
	*/
	void    AddPoint(PEN_DATA data);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ��ȡ��������
	*/
	bool    GetDrawItem(DRAW_ITEM &data);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ����
	*/
	int    Undo();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ����
	*/
	int    Redo();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���
	*/
	void    Clear();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : ��ȡ��ͼ������Ϣ
	*/
	void GetQueSize(int &RedoSize, int &UndoSize);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : ��ȡ�ʵ���˳��
	*/
	int GetPenid();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : ���ñʵ���˳��
	*/
	void SetPenid(int nPenid);


	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���û��ʴ�С
	*/
	void    SetPenSize(int nSize);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���û�����ɫ
	*/
	void    SetPenColor(const QColor &color);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���û�������
	*/
	void    SetPenType(DRAW_TYPE nType);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ������Ƥ����С
	*/
	void    SetEraseSize(int nSize);



	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-24
	* Describe : �����һ�λ��ƹ켣
	*/
	void    ClearLastDrawItem();


	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : ���¿�ʼ
	*/
	void    ReStart();


	//�̳�
protected:

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-25
	* Describe : �����¼�
	*/
	void paintEvent(QPaintEvent * e);


private:
	int                 m_nEraseSize;       //��Ƥ����С
	int                 m_nPenSize;         //�ʼ���С
	QColor              m_penColor;         //�ʼ���ɫ

	QVector<PEN_DATA>   m_vectAllData;      //����������Ϣ
	QVector<QPoint>     m_vectDrawData;     //����������Ϣ
	int                 m_nPenId;           //�ʼ�ID˳��
	bool                m_bFlagDrawing;     //���ڻ��Ʊ�ʶ
	bool                m_bFlagClear;       //�����ʶ
	PEN_STATE           m_penState;         //�����״̬
	QColor              m_bkColor;          //������ɫ

	QQueue<DRAW_ITEM>   m_queDrawItem;      //�������

	QQueue<DRAW_ITEM>   m_queRedoItem;      //��������

	DRAW_ITEM           m_drawItem;         //���ڻ���
};

#endif // DRAWWIDGET_H
