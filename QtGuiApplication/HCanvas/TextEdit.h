/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file BaseShape.h
* @summary 重写文本编辑框
*
* @version 1.0
* @author zhengzc@wangsu.com
* @date 2018-03-06 14:25:06
*
* @others
* @MODIFY    VERSION  YYYYMMDD    TITLE
* zhengzc     1.0     20180306     title
*
*/
#pragma once
#include <QTextEdit>

class CTextEdit:public QTextEdit
{
	Q_OBJECT
public:
	CTextEdit(QWidget *parent);
	~CTextEdit();

	/**
	* Describe : 设置输入框字体
	* Param	   : font : 输入的字体
	* Return   : void
	*/
	void setDrawFont(QFont font);
private:

	/**
	* Describe : 焦点进入事件
	* Param	   : pEvent ：焦点事件指针
	* Return   : void
	*/
	virtual void focusInEvent(QFocusEvent *pEvent);

	/**
	* Describe : 焦点失去
	* Param	   : pEvent ：焦点事件指针
	* Return   : void
	*/
	virtual void focusOutEvent(QFocusEvent *pEvent);

	/**
	* Describe : 绘制事件
	* Param	   : pEvent ：绘制事件指针
	* Return   : void
	*/
	void paintEvent(QPaintEvent *pEvent);
	//信号槽 之槽的接口
public slots:

	void slot_textChanged();

	//信号槽 之信号定义
signals:

	void sig_draw_text(QRect rect, QString strText);
private:
	QFont	m_font;			//保存当前的字体
};

