
#include <windows.h>

#include <QApplication>
#include <QDebug>

#include "QWhiteBoard.h"
#include "qmfcapp.h"
#include "QtWsWidget.h"




static bool ownApplication = FALSE;
static  HINSTANCE  g_hInstance = 0;

/**  
* @brief dll�������  
* @param   
* @return ���ؼ��ؽ��  
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

/*****************************�����ӿ�*******************************/

/***********************
//�����װ�
//p:������ָ��,nX :�װ��X����,nY:�װ��Y����
//nWidth:�װ�Ŀ�,nHight�װ�ĸ�
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

//��ʾ�װ�
QWHITEBOARD_EXPORT void WhiteBoard_Show()
{


}

//���ذװ�
QWHITEBOARD_EXPORT void WhiteBoard_Hide()
{


}

/*********************************/
//�ƶ��װ�
//nX :�װ��X����,nY:�װ��Y����
/************************************/
QWHITEBOARD_EXPORT void WhiteBoard_Move(int nX, int nY)
{


}

/************************************/
//���İװ�ߴ�
//nWidth:�װ�Ŀ�,nHight�װ�ĸ�
/************************************/
QWHITEBOARD_EXPORT void WhiteBoard_SetSize(int nWidth, int nHight) 
{


}

//�رհװ�
QWHITEBOARD_EXPORT void WhiteBoard_Close()
{


}


/************************************/
//���ûص�
//pFuncEngineCallback:�ص�����
/************************************/
QWHITEBOARD_EXPORT void WhiteBoard_SetEngineCallback(pFuncEngineCallback pFun)
{



}





