/**  * @copyright (C) 2016 ChinaNetCenter Inc. All rights reserved.
*
* @file DrawArrow.h
* @summary ¼ýÍ·»æÖÆ
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

class CDrawArrow : public CBaseShape
{
public:
	CDrawArrow();

	void paintDrawItem(QPainter& paint) override;

	virtual int getDrawType() override;
};

