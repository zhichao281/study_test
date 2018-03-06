#ifndef CANVASMODELDEF_H
#define CANVASMODELDEF_H

#include <QString>
#include <QPoint>
#include <QColor>


//笔迹类型
enum DRAW_TYPE
{
    DT_NULL     = 0,
    DT_TRACE,               //轨迹
    DT_UNDO,                //撤销
    DT_CLEAR,               //清屏
    DT_VECTORGRAPH,         //矢量图
    DT_PAGE_SCROLL,         //页面滚动
    DT_IMAGE,               //图片
    DT_ERASE,               //橡皮
};

//点阵笔状态
enum PEN_STATE
{
    PS_NULL     = 0,
    PS_DOWN,                //落下
    PS_WRITE,               //书写
    PS_UP,                  //抬起
};

//笔迹数据
struct PEN_DATA
{
    int         nSize;      //笔迹大小
    QColor      color;      //颜色
    QString     strCursor;  //鼠标类型
    DRAW_TYPE   nPenType;   //笔迹类型
    PEN_STATE   nPenState;  //点阵笔状态
    QPoint      pos;        //坐标
    quint64     nTimestamp; //时间戳
    int         nPenId;     //笔迹ID
    int         nChangeId;  //修改的ID
    QString     strPen ;    //笔迹信息


    PEN_DATA()
    {
        nSize       = 1;
        nPenType    = DT_NULL;
        nPenState   = PS_NULL;
        nTimestamp  = 0;

    }
};

//绘制信息
struct DRAW_ITEM
{
    PEN_DATA        penData;    //笔迹数据
    QPoint          posBegin;   //起始点
    QPoint          posEnd;     //结束点
    QString         strText;    //文本

    QVector<quint64>    vectTimestamp;  //笔迹时间戳
    QVector<QPoint>     vectPath;       //笔迹路径
    void    Init()
    {
        penData     = PEN_DATA();
        posBegin    = QPoint();
        posEnd      = QPoint();
        strText.clear();
        vectTimestamp.clear();
        vectPath.clear();
    }
};

#endif // CANVASMODELDEF_H
