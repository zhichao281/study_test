#include <QApplication>
#include "QtGuiApplication.h"
#include <QtWidgets/QApplication>

#include <stdio.h>
#include <windows.h>

//定义函数指针
typedef bool(*showDialog)(HWND);


typedef void (*WhiteBoard)(HWND hfather, int nX, int nY, int nWidth, int nHight);
//#include "D:\\download\\qt-solutions-master\\qtwinmigrate\\src\\qwinwidget.h"
#include "../QWhiteBoard/QWhiteBoard.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#ifdef _DEBUG
#pragma comment(lib,"E:\\study\\study_test\\x64\\Debug\\QWhiteBoard.lib")
#else
#pragma comment(lib,"..\\release\\LedCtrlBoard.lib")
#endif
#include "mainwindows.h"
int main(int argc, char *argv[])
{
		QApplication a(argc, argv);
		MainWindow w;
		w.show();

		//WhiteBoard_Create((HWND)w.winId(), 0, 0, 0, 0);


		return a.exec();
		//定义DLL句柄
		//HINSTANCE hDll = LoadLibraryA("e:/QWhiteBoard.dll");
		//if (hDll != NULL)
		//{
		//	WhiteBoard WhiteBoard_Create1 = (WhiteBoard)GetProcAddress(hDll, "WhiteBoard_Create");
		//	WhiteBoard_Create1((HWND)w.winId(), 0, 0, 0, 0);

		//}
		
	
	
	
	

	//QWinWidget w1((HWND)w.winId());
	//w1.show();
	//FreeLibrary(hDll);
	
}