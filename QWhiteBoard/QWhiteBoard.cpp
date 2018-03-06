
#include <windows.h>

#include <QApplication>
#include <QDebug>

#include "QWhiteBoard.h"
#include "qmfcapp.h"
#include "QtWsWidget.h"




static bool ownApplication = FALSE;
static  HINSTANCE  g_hInstance = 0;

/**  
* @brief dll的主入口  
* @param   
* @return 返回加载结果  
*/
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	static bool ownApplication = FALSE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		g_hInstance = hInstance;
		//ownApplication = QMfcApp::pluginInstance(hInstance);
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		if (ownApplication)
		{
			qApp->quit();
			delete qApp;
		}
	}
	default:
		break;
	}

	return TRUE;
}
QWhiteBoard::QWhiteBoard()
{
}

/*****************************导出接口*******************************/

/***********************
//创建白板
//p:主窗体指针,nX :白板的X坐标,nY:白板的Y坐标
//nWidth:白板的宽,nHight白板的高
*********************/
QWHITEBOARD_EXPORT void WhiteBoard_Create(HWND hfather, int nX, int nY, int nWidth, int nHight)
{
	if (g_hInstance !=0 && ownApplication == false)
	{
		ownApplication = QMfcApp::pluginInstance(g_hInstance);
	}

	gblQtWsWidgetGet->WhiteBoard_Create(hfather,nX,nY,nWidth,nHight);
	 return;

}

//显示白板
QWHITEBOARD_EXPORT void WhiteBoard_Show()
{


}

//隐藏白板
QWHITEBOARD_EXPORT void WhiteBoard_Hide()
{


}

/*********************************/
//移动白板
//nX :白板的X坐标,nY:白板的Y坐标
/************************************/
QWHITEBOARD_EXPORT void WhiteBoard_Move(int nX, int nY)
{


}

/************************************/
//更改白板尺寸
//nWidth:白板的宽,nHight白板的高
/************************************/
QWHITEBOARD_EXPORT void WhiteBoard_SetSize(int nWidth, int nHight) 
{


}

//关闭白板
QWHITEBOARD_EXPORT void WhiteBoard_Close()
{


}


/************************************/
//设置回调
//pFuncEngineCallback:回调函数
/************************************/
QWHITEBOARD_EXPORT void WhiteBoard_SetEngineCallback(pFuncEngineCallback pFun)
{



}





