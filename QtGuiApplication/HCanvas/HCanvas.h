/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file paintWidget.h
* @summary 白板接口层
*
* @version 1.0
* @author zhengzc@wangsu.com
* @date 2018-03-12 09:25:06
*
* @others
* @MODIFY    VERSION  YYYYMMDD    TITLE
* zhengzc      1.0    20180312    title
*
*/




#pragma  once 
#include <memory>

#include <QWidget>
#include <QMenu>

#include "paintWidget.h"

//白板输出层
class HCanvas : public QWidget
{
	Q_OBJECT
public:
	/** 默认构造函数 */
	explicit HCanvas(QWidget *parent = 0);

	/** 默认析构函数 */
	~HCanvas();

	//信号槽的信号定义
signals:
	/**
	* Describe : 改变是否笔直绘画的信号
	* Param	   :  bStraight true 强制x=y,flase x y值不相关
	* Return   : void
	*/
	void sig_change_straight(bool bStraight);

	/**
	* Describe : 设置绘图形状的信号
	* Param	   : new_shape 图形形状枚举
	* Return   : void
	*/
	void sig_set_shape(DRAW_TYPE new_shape);
	/**
	* Describe : 设置画笔颜色调整信号
	* Param	   : penColor 画笔颜色
	* Return   : void
	*/
	void sig_set_penColor(QColor penColor);

	/**
	* Describe : 设置填充颜色调整的信号
	* Param	   : brushColor 填充色
	* Return   : void
	*/
	void sig_set_brushColor(QColor brushColor);
	
	/**
	* Describe : 设置橡皮擦大小
	* Param	   : nEraseSize 橡皮擦大小
	* Return   : void
	*/
	void  sig_set_EraseSize(int nEraseSize);

	/**
	* Describe : 设置线条粗细的信号
	* Param	   : nPenSize 画笔尺寸
	* Return   : void
	*/
	void sig_set_penSize(int nPenSize);	
	

	/**
	* Describe : 设置填充色的透明度的信号
	* Param	   : nAlpha 透明值 0-100
	* Return   : void
	*/
	void sig_set_brushAlpha(int nAlpha);

	/**
	* Describe : 撤销
	* Param	   : void
	* Return   : void
	*/
	void sig_Undo();

	/**
	* Describe : 重做
	* Param	   : void
	* Return   : void
	*/
	void sig_Redo();

	/**
	* Describe : 重置
	* Param	   : void
	* Return   : void
	*/
	void sig_Reset();


	//导出接口
public:

	/**
	* Describe : 设置背景图片
	* Param	   : strFile 导入图片路径
	* Return   : void
	*/
	bool    setBackgroundImage(QString strFile);


	/**
	* Describe : 获取画布内容
	* Param	   : pixmap 图片
	* Return   : void
	*/
	void    GetImage(QPixmap &pixmap);

	//内部使用接口
protected:

	/**
	* Describe : 初始化
	* Param	   : void
	* Return   : void
	*/
	void    _Init();

	/**
	* Describe : 信号槽绑定
	* Param	   : void
	* Return   : void
	*/
	void SignalBinding();

	//继承
protected:

	//槽事件
public slots :


		void test(DRAW_TYPE n1);


private:

	std::shared_ptr<CPaintWidget>          m_drawWidget;     //绘图区域

	
};


