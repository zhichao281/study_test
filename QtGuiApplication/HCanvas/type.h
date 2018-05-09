#pragma once

#pragma execution_character_set("utf-8")
//清除内存
#define SAFE_DELETE(x)              { if(NULL != x) { try{ delete x; } catch(...) { } x = NULL; }}               //删除指针
#define SAFE_FREE(x)                { if(NULL != x) { free(x); x = NULL; }}                                      //释放堆内存
#define SAFE_RELEASE(x)             { if(NULL != x) { x->Release(); x = NULL; }}                                 //释放接口
#define SAFE_CLOSEHANDLE(x)         { if(NULL != x && INVALID_HANDLE_VALUE != x) { CloseHandle(x); x = NULL; }}  //关闭句柄
#define SAFE_DELETEARRAY(x)         { if(NULL != x) { try{ delete [] x; } catch(...) { } x = NULL; }}            //删除数组

//绘制的形状类型
enum DRAW_TYPE 
{ 
	Draw_Rect =1,		 //方形
	Draw_Line,			 //直线
	Draw_Pen,			 //画笔
	Draw_Ellipse,		 //椭圆
	Draw_Polygon,		 //多边形
	Draw_Erase,			 //橡皮擦
	Draw_Text,			 //文本
	Draw_Arrow			 //箭头
};

