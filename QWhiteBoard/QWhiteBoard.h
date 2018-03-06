/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved. 
*  
* @file QWhiteBoard.h 
* @summary ���ڵ����ӿ�
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
* @brief �����װ�  
* @param hfather:��������,nX:�װ��X����,nY:�װ��Y����
//nWidth:�װ�Ŀ�,nHight�װ�ĸ�
* @return ����ת�����  
*/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Create(HWND hfather, int nX, int nY, int nWidth, int nHight);

/************************************/
//��ʾ�װ�
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Show();
/************************************/
//���ذװ�
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Hide();

/*********************************/
//�ƶ��װ�
//nX :�װ��X����,nY:�װ��Y����
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Move(int nX, int nY);

/************************************/
//���İװ�ߴ�
//nWidth:�װ�Ŀ�,nHight�װ�ĸ�
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_SetSize(int nWidth, int nHight);

/************************************/
//�رհװ�
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_Close();


/************************************/
//���ûص�
//pFuncEngineCallback:�ص�����
/************************************/
extern "C" QWHITEBOARD_EXPORT void WhiteBoard_SetEngineCallback(pFuncEngineCallback pFun);



