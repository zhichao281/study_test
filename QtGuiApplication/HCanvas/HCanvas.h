/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file paintWidget.h
* @summary �װ�ӿڲ�
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

//�װ������
class HCanvas : public QWidget
{
	Q_OBJECT
public:
	/** Ĭ�Ϲ��캯�� */
	explicit HCanvas(QWidget *parent = 0);

	/** Ĭ���������� */
	~HCanvas();

	//�źŲ۵��źŶ���
signals:
	/**
	* Describe : �ı��Ƿ��ֱ�滭���ź�
	* Param	   :  bStraight true ǿ��x=y,flase x yֵ�����
	* Return   : void
	*/
	void sig_change_straight(bool bStraight);

	/**
	* Describe : ���û�ͼ��״���ź�
	* Param	   : new_shape ͼ����״ö��
	* Return   : void
	*/
	void sig_set_shape(DRAW_TYPE new_shape);
	/**
	* Describe : ���û�����ɫ�����ź�
	* Param	   : penColor ������ɫ
	* Return   : void
	*/
	void sig_set_penColor(QColor penColor);

	/**
	* Describe : ���������ɫ�������ź�
	* Param	   : brushColor ���ɫ
	* Return   : void
	*/
	void sig_set_brushColor(QColor brushColor);
	
	/**
	* Describe : ������Ƥ����С
	* Param	   : nEraseSize ��Ƥ����С
	* Return   : void
	*/
	void  sig_set_EraseSize(int nEraseSize);

	/**
	* Describe : ����������ϸ���ź�
	* Param	   : nPenSize ���ʳߴ�
	* Return   : void
	*/
	void sig_set_penSize(int nPenSize);	
	

	/**
	* Describe : �������ɫ��͸���ȵ��ź�
	* Param	   : nAlpha ͸��ֵ 0-100
	* Return   : void
	*/
	void sig_set_brushAlpha(int nAlpha);

	/**
	* Describe : ����
	* Param	   : void
	* Return   : void
	*/
	void sig_Undo();

	/**
	* Describe : ����
	* Param	   : void
	* Return   : void
	*/
	void sig_Redo();

	/**
	* Describe : ����
	* Param	   : void
	* Return   : void
	*/
	void sig_Reset();


	//�����ӿ�
public:

	/**
	* Describe : ���ñ���ͼƬ
	* Param	   : strFile ����ͼƬ·��
	* Return   : void
	*/
	bool    setBackgroundImage(QString strFile);


	/**
	* Describe : ��ȡ��������
	* Param	   : pixmap ͼƬ
	* Return   : void
	*/
	void    GetImage(QPixmap &pixmap);

	//�ڲ�ʹ�ýӿ�
protected:

	/**
	* Describe : ��ʼ��
	* Param	   : void
	* Return   : void
	*/
	void    _Init();

	/**
	* Describe : �źŲ۰�
	* Param	   : void
	* Return   : void
	*/
	void SignalBinding();

	//�̳�
protected:

	//���¼�
public slots :


		void test(DRAW_TYPE n1);


private:

	std::shared_ptr<CPaintWidget>          m_drawWidget;     //��ͼ����

	
};


