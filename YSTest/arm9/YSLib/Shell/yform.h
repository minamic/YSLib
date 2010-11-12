﻿/*
	Copyright (C) by Franksoft 2010.

	This file is part of the YSLib project, and may only be used,
	modified, and distributed under the terms of the YSLib project
	license, LICENSE.TXT.  By continuing to use, modify, or distribute
	this file you indicate that you have read the license and
	understand and accept it fully.
*/

/*!	\file yform.h
\ingroup Shell
\brief 平台无关的 GUI 窗体实现。
\version 0.1410;
\author FrankHB<frankhb1989@gmail.com>
\par 创建时间:
	2010-04-30 00:51:36 + 08:00;
\par 修改时间:
	2010-11-12 18:31 + 08:00;
\par 字符集:
	UTF-8;
\par 模块名称:
	YSLib::Shell::YForm;
*/


#ifndef INCLUDED_YFORM_H_
#define INCLUDED_YFORM_H_

#include "ywindow.h"

YSL_BEGIN

YSL_BEGIN_NAMESPACE(Components)

YSL_BEGIN_NAMESPACE(Forms)

//窗体。
class YForm : public GMCounter<YForm>, public YFrameWindow
{
public:
	typedef YFrameWindow ParentType;

//	Widgets::YUIContainer Client;

protected:

public:
	/*!
	\brief 构造：使用指定边界、背景、桌面、 Shell 和父窗口。
	*/
	explicit
	YForm(const Rect& = Rect::Empty, const GHResource<YImage> = new YImage(),
		YDesktop* = ::YSLib::pDefaultDesktop,
		HSHL = ::YSLib::theApp.GetShellHandle(), HWND = NULL);
	/*!
	\brief 析构。
	\note 无异常抛出。
	*/
	virtual
	~YForm() ythrow();

/*	virtual void
	SetSize(SDST, SDST);
	virtual void
	SetBounds(const Rect&);

protected:
	virtual void
	DrawBackground();

	virtual void
	DrawForeground();

public:
	virtual void
	Draw();
*/
};

YSL_END_NAMESPACE(Forms)

YSL_END_NAMESPACE(Components)

YSL_END

#endif

