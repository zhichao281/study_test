/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved. 
*  
* @file QWhiteBoard.h 
* @summary 用于导出接口
*  
* @version 1.0  
* @author zzc@chinanetcenter.com  
* @date 2016-03-16 14:25:06  
*  
* @others  
* @MODIFY    VERSION  YYYYMMDD    TITLE  
*   zzc      1.0     20180301     title   
* 
*/
 


#pragma once


#ifndef BUILD_STATIC
#if defined(QWHITEBOARD_LIB)
#define QWHITEBOARD_EXPORT __declspec(dllexport)
#else
#define QWHITEBOARD_EXPORT __declspec(dllimport)
#endif
#else
# define QWHITEBOARD_EXPORT
#endif

#include <windows.h>

class QWHITEBOARD_EXPORT QWhiteBoard
{
public:
	QWhiteBoard();
};

using namespace std;

typedef void(*pFuncEngineCallback)(int, int, wchar_t*);

/**  
* @brief 创建白板  
* @param hfather:主窗体句柄,nX:白板的X坐标,nY:白板的Y坐标
//nWidth:白板的宽,nHight白板的高
* @return 返回转换结果  
*/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Create(HWND hfather, int nX, int nY, int nWidth, int nHight);

/************************************/
//显示白板
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Show();
/************************************/
//隐藏白板
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Hide();

/*********************************/
//移动白板
//nX :白板的X坐标,nY:白板的Y坐标
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Move(int nX, int nY);

/************************************/
//更改白板尺寸
//nWidth:白板的宽,nHight白板的高
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_SetSize(int nWidth, int nHight);

/************************************/
//关闭白板
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Close();


/************************************/
//设置回调
//pFuncEngineCallback:回调函数
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_SetEngineCallback(pFuncEngineCallback pFun);



