/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file DrawEllipse.h
* @summary ‘≤–ŒªÊ÷∆
*
* @version 1.0
* @author zhengzc@wangsu.com
* @date 2018-03-07 14:25:06
*
* @others
* @MODIFY    VERSION  YYYYMMDD    TITLE
* zhengzc     1.0     20180307     title
*
*/
#pragma once

#include "BaseShape.h"  

class CDrawEllipse : public CBaseShape
{
public:

	CDrawEllipse();
private: 

	virtual void paintDrawItem(QPainter& paint) override;

	virtual int getDrawType() override;
};


