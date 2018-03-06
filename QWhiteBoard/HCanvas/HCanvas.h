#ifndef HCANVAS_H
#define HCANVAS_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <memory>
#include <QTemporaryDir>


#include "CanvasModelDef.h"
#include "ImageWidget.h"
#include "DrawWidget.h"
#include "BkImageWidget.h"
class HCanvas : public QWidget
{
	Q_OBJECT
public:
	explicit HCanvas(QWidget *parent = 0);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ���ñ���ͼƬ
	*/
	bool    SetBkImage(QString strFile);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ������Ƥ����С
	*/
	void    SetEraseSize(int nSize);

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
	* Describe : ��ӵ�
	*/
	void    AddPoint(PEN_DATA data);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-24
	* Describe : �����һ�λ��ƹ켣
	*/
	void    ClearLastDrawItem();

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
	* DateTime : 2017-08-21
	* Describe : ���¿�ʼ
	*/
	void    ReStart();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : ��ȡ��������
	*/
	void    GetImage(QPixmap &pixmap);

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
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : ���ͼƬ
	*/
	int addPic(QString strFile, bool bRecord);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : ���ͼƬ
	*/
	int addPic(QImage image, bool bRecord);



	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : �����Ҽ��˵�
	*/
	void createMenu();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : �����Ҽ��˵�����
	*/
	void createAction();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : ��ȡ��ͼ������Ϣ
	*/
	void GetQueSize(int &RedoSize, int &UndoSize);


	/*
	* Author   : zhengzc
	* DateTime : 2017-08-30
	* Describe : �����ͼ��Ϣ
	*/
	void ClearDrawData();

	/*
	* Author   : zhengzc
	* DateTime : 2017-09-07
	* Describe : ��ȡ�ļ�ͷ
	*/
	QString GetFileHead(QString strPath);

	/*
	* Author   : zhengzc
	* DateTime : 2017-09-07
	* Describe : �����ļ�����ʱĿ¼
	*/
	QString CoptToTempFile(QString sourceDir);
protected:
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
	* Describe : ���Ʊʼ�
	*/
	void    _DrawCoordinate(int nFrom, int nTo);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : �������
	*/
	void    _CalcRect(QRect &rt, QPoint posBegin, QPoint posEnd);


	//�̳�
protected:

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-18
	* Describe : ��갴���¼�
	*/
	void mousePressEvent(QMouseEvent *e);

	/*
	* Author   :  zhengzc
	* DateTime : 2017-08-18
	* Describe : ����ƶ��¼�
	*/
	void mouseMoveEvent(QMouseEvent *e);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-18
	* Describe : ����ͷ��¼�
	*/
	void mouseReleaseEvent(QMouseEvent *e);




	void resizeEvent(QResizeEvent *event);




public slots:

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : �Ҽ��˵�
	*/
	void On_Slot_ContextMenu(QPoint);

signals:




private:
	int                 m_nPenId;           //�ʼ�ID˳��

	QPoint                  m_startPnt;               //���
	QPoint                  m_endPnt;                 //�յ�
	bool                    m_bPressed;             //����Ƿ���
	QTemporaryDir       dir;                //��ʱ�ļ���λ��
	QString             m_TempDir;          //����ͼƬ����·��
	QMenu               * m_menu;           //�Ҽ��˵�
	QAction             * m_copyAction;		//��������
	QAction             * m_clearAction;	//�������
	QAction             * m_RotateAction;	//��ת����
	ImageWidget         *m_MenuImage;       //�Ҽ�ָ���ͼƬ

	std::shared_ptr<CDrawWidget>          m_drawWidget;     //��ͼ����

	std::shared_ptr<CBkImageWidget>       m_bskWidget;    //����ͼ����
	

};




#endif // HCANVAS_H
