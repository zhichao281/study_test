#pragma once

#pragma execution_character_set("utf-8")
//����ڴ�
#define SAFE_DELETE(x)              { if(NULL != x) { try{ delete x; } catch(...) { } x = NULL; }}               //ɾ��ָ��
#define SAFE_FREE(x)                { if(NULL != x) { free(x); x = NULL; }}                                      //�ͷŶ��ڴ�
#define SAFE_RELEASE(x)             { if(NULL != x) { x->Release(); x = NULL; }}                                 //�ͷŽӿ�
#define SAFE_CLOSEHANDLE(x)         { if(NULL != x && INVALID_HANDLE_VALUE != x) { CloseHandle(x); x = NULL; }}  //�رվ��
#define SAFE_DELETEARRAY(x)         { if(NULL != x) { try{ delete [] x; } catch(...) { } x = NULL; }}            //ɾ������

//���Ƶ���״����
enum DRAW_TYPE 
{ 
	Draw_Rect =1,		 //����
	Draw_Line,			 //ֱ��
	Draw_Pen,			 //����
	Draw_Ellipse,		 //��Բ
	Draw_Polygon,		 //�����
	Draw_Erase,			 //��Ƥ��
	Draw_Text,			 //�ı�
	Draw_Arrow			 //��ͷ
};

