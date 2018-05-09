/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file BaseShape.h
* @summary ��д�ı��༭��
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
	* Describe : �������������
	* Param	   : font : ���������
	* Return   : void
	*/
	void setDrawFont(QFont font);
private:

	/**
	* Describe : ��������¼�
	* Param	   : pEvent �������¼�ָ��
	* Return   : void
	*/
	virtual void focusInEvent(QFocusEvent *pEvent);

	/**
	* Describe : ����ʧȥ
	* Param	   : pEvent �������¼�ָ��
	* Return   : void
	*/
	virtual void focusOutEvent(QFocusEvent *pEvent);

	/**
	* Describe : �����¼�
	* Param	   : pEvent �������¼�ָ��
	* Return   : void
	*/
	void paintEvent(QPaintEvent *pEvent);
	//�źŲ� ֮�۵Ľӿ�
public slots:

	void slot_textChanged();

	//�źŲ� ֮�źŶ���
signals:

	void sig_draw_text(QRect rect, QString strText);
private:
	QFont	m_font;			//���浱ǰ������
};

