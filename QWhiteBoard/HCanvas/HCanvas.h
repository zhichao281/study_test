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
	* Describe : 设置背景图片
	*/
	bool    SetBkImage(QString strFile);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 设置橡皮擦大小
	*/
	void    SetEraseSize(int nSize);

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
	* Describe : 添加点
	*/
	void    AddPoint(PEN_DATA data);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-24
	* Describe : 清除上一次绘制轨迹
	*/
	void    ClearLastDrawItem();

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
	* DateTime : 2017-08-21
	* Describe : 重新开始
	*/
	void    ReStart();

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 获取画布内容
	*/
	void    GetImage(QPixmap &pixmap);

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
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : 添加图片
	*/
	int addPic(QString strFile, bool bRecord);
	/*
	* Author   : zhengzc
	* DateTime : 2017-08-21
	* Describe : 添加图片
	*/
	int addPic(QImage image, bool bRecord);



	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 创建右键菜单
	*/
	void createMenu();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 创建右键菜单动作
	*/
	void createAction();

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 获取绘图队列信息
	*/
	void GetQueSize(int &RedoSize, int &UndoSize);


	/*
	* Author   : zhengzc
	* DateTime : 2017-08-30
	* Describe : 清理绘图信息
	*/
	void ClearDrawData();

	/*
	* Author   : zhengzc
	* DateTime : 2017-09-07
	* Describe : 获取文件头
	*/
	QString GetFileHead(QString strPath);

	/*
	* Author   : zhengzc
	* DateTime : 2017-09-07
	* Describe : 拷贝文件到临时目录
	*/
	QString CoptToTempFile(QString sourceDir);
protected:
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
	* Describe : 绘制笔迹
	*/
	void    _DrawCoordinate(int nFrom, int nTo);

	/*
	* Author   : Zhengzc
	* DateTime : 2017-07-06
	* Describe : 计算矩形
	*/
	void    _CalcRect(QRect &rt, QPoint posBegin, QPoint posEnd);


	//继承
protected:

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-18
	* Describe : 鼠标按下事件
	*/
	void mousePressEvent(QMouseEvent *e);

	/*
	* Author   :  zhengzc
	* DateTime : 2017-08-18
	* Describe : 鼠标移动事件
	*/
	void mouseMoveEvent(QMouseEvent *e);

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-18
	* Describe : 鼠标释放事件
	*/
	void mouseReleaseEvent(QMouseEvent *e);




	void resizeEvent(QResizeEvent *event);




public slots:

	/*
	* Author   : zhengzc
	* DateTime : 2017-08-28
	* Describe : 右键菜单
	*/
	void On_Slot_ContextMenu(QPoint);

signals:




private:
	int                 m_nPenId;           //笔迹ID顺序

	QPoint                  m_startPnt;               //起点
	QPoint                  m_endPnt;                 //终点
	bool                    m_bPressed;             //鼠标是否按下
	QTemporaryDir       dir;                //临时文件夹位置
	QString             m_TempDir;          //背景图片保存路径
	QMenu               * m_menu;           //右键菜单
	QAction             * m_copyAction;		//拷贝动作
	QAction             * m_clearAction;	//清除动作
	QAction             * m_RotateAction;	//旋转操作
	ImageWidget         *m_MenuImage;       //右键指向的图片

	std::shared_ptr<CDrawWidget>          m_drawWidget;     //绘图区域

	std::shared_ptr<CBkImageWidget>       m_bskWidget;    //背景图区域
	

};




#endif // HCANVAS_H
