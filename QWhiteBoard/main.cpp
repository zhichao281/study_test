#include <QDebug>
#include <windows.h>

#include "qmfcapp.h"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	static bool ownApplication = FALSE;

	if (dwReason == DLL_PROCESS_ATTACH)
		ownApplication = QMfcApp::pluginInstance(hInstance);
	if (dwReason == DLL_PROCESS_DETACH && ownApplication)
		delete qApp;

	return TRUE;
}
2222
