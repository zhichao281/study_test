#pragma once


#include <QColorDialog>  
#include <QInputDialog>  
#include <QActionGroup>  
#include <QFileDialog>  
#include <QMainWindow>  
#include <QKeyEvent>  
#include <QToolBar>  
#include <QMenuBar>  
#include <QSlider>  
#include <QAction>  
#include <QColor>  
#include <QLabel>  
#include <QMenu>  
#include <QDial>  


#include "../HCanvas/paintWidget.h"  
#include "../HCanvas/type.h"  
#include "../HCanvas/HCanvas.h"  
#include "../ToolBar/ToolBarWidget.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void keyPressEvent(QKeyEvent *);    //�����¼�  
	void keyReleaseEvent(QKeyEvent *);  //�����¼� 
	virtual QSize sizeHint() const override;//��������ĺ���  
signals:

	void openFile_SIGNAL(QString);
	void saveFile_SIGNAL(QString);      //�ļ������ź�  

	void change_straight(bool);          //�ı��Ƿ��ֱ�滭���ź�  

	void color_change(QColor);          ///���Ե����ź�  
	void brush_change(QColor);
	void width_change(int);         //����������ϸ���ź�  
	void alpha_change(int);         //����͸���ȵ��ź�  

	void select_shape(DRAW_TYPE);      //ѡ����״�ź�  


private slots:
	void change_widthLabel(int);        ///�ı����ԵĲ�  
	void change_alphaLabel(int);
	void color_SLOT();
	void brush_SLOT();
	void width_SLOT();

	void draw_rect();           ///���Ʋ�  
	void draw_line();
	void draw_pen();
	void draw_erase();
	void draw_polygon();
	void draw_ellipse();
	void draw_text();

	void draw_Arrow();

	void draw_Image();

	void reset_dial();      //�������  

	void On_Slot_ChangePenStates();

	
private:
	HCanvas * m_pCanvas;
	QLabel * widthLabel;     //��ʾ��ǰ������С  
	QDial *widthDial;
	QLabel *alphaLabel;     //��ʾ��ǰ͸����  
	QDial *alphaDial;

	CToolBarWidget          *m_pToolBarWidget;      //����������

};

