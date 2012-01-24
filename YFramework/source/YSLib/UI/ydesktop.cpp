﻿/*
	Copyright (C) by Franksoft 2010 - 2012.

	This file is part of the YSLib project, and may only be used,
	modified, and distributed under the terms of the YSLib project
	license, LICENSE.TXT.  By continuing to use, modify, or distribute
	this file you indicate that you have read the license and
	understand and accept it fully.
*/

/*!	\file ydesktop.cpp
\ingroup UI
\brief 平台无关的桌面抽象层。
\version r2386;
\author FrankHB<frankhb1989@gmail.com>
\since 早于 build 132 。
\par 创建时间:
	2010-05-02 12:00:08 +0800;
\par 修改时间:
	2012-01-23 01:55 +0800;
\par 文本编码:
	UTF-8;
\par 模块名称:
	YSLib::UI::Desktop;
*/


#include "YSLib/UI/ydesktop.h"

YSL_BEGIN

using namespace Drawing;

YSL_BEGIN_NAMESPACE(Components)

Desktop::Desktop(Devices::Screen& s, Color c, const shared_ptr<Image>& hImg)
	: Window(Rect::FullScreen, hImg),
	screen(s)
{
	BackColor = c,
	GetBufferedRenderer().IgnoreBackground = true;
}

void
Desktop::Update()
{
	if(!GetBufferedRenderer().RequiresRefresh())
		screen.Update(GetContext().GetBufferPtr());
}

Rect
Desktop::Validate()
{
	return GetBufferedRenderer().Validate(*this, PaintContext(GetContext(),
		Point::Zero, GetBoundsOf(*this)));
}

YSL_END_NAMESPACE(Components)

YSL_END

