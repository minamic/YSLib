﻿/*
	Copyright (C) by Franksoft 2010 - 2011.

	This file is part of the YSLib project, and may only be used,
	modified, and distributed under the terms of the YSLib project
	license, LICENSE.TXT.  By continuing to use, modify, or distribute
	this file you indicate that you have read the license and
	understand and accept it fully.
*/

/*!	\file DSReader.cpp
\ingroup YReader
\brief 适用于 DS 的双屏阅读器。
\version r3217;
\author FrankHB<frankhb1989@gmail.com>
\par 创建时间:
	2010-01-05 14:04:05 +0800;
\par 修改时间:
	2011-09-25 19:27 +0800;
\par 字符集:
	UTF-8;
\par 模块名称:
	YReader::DSReader;
*/


#include "DSReader.h"

YSL_BEGIN

YSL_BEGIN_NAMESPACE(DS)

using namespace Drawing;
using namespace Text;

YSL_BEGIN_NAMESPACE(Components)

BlockedText::BlockedText(TextFile& file)
	: File(file), Blocks(file)
{}


MDualScreenReader::MDualScreenReader(SDst w, SDst h_up, SDst h_down,
	FontCache& fc_)
try	: pText(), fc(fc_),
	rot(RDeg0), itUp(), itDn(),
	cp(Text::CharSet::Null),
	AreaUp(Rect(Point::Zero, w, h_up), fc),
	AreaDown(Rect(Point::Zero, w, h_down), fc)
{
	SetFontSize();
	SetColor();
	SetLineGap();
	AreaUp.SetTransparent(true);
	AreaDown.SetTransparent(true);
}
catch(LoggedEvent&)
{
	throw;
}

/*
void MDualScreenReader::SetCurrentTextLineNOf(u8 n)
{
	if(n >= 0)
		AreaUp.SetCurrentTextLineNOf(n);
}
*/

void
MDualScreenReader::Invalidate()
{
	using YSLib::Components::Invalidate;

	//强制刷新背景。
	Invalidate(AreaUp);
	Invalidate(AreaDown);
}

bool
MDualScreenReader::LineUp()
{
	if(IsTextTop())
		return false;

	const u8 h = lnHeight, hx = h + GetLineGapDown();
	const SDst w = AreaUp.GetWidth();
	const u32 t = w * h,
		s = (AreaUp.GetHeight() - FetchResizedMargin(AreaUp,
			AreaUp.GetHeight()) - h) * w,
		d = AreaDown.Margin.Top * w;

	AreaDown.Scroll(hx, FetchResizedBufferHeight(AreaDown,
		AreaDown.GetHeight()));
	std::memcpy(&AreaDown.GetBufferPtr()[d],
		&AreaUp.GetBufferPtr()[s], t * sizeof(PixelType));
	std::memcpy(&AreaDown.GetBufferAlphaPtr()[d],
		&AreaUp.GetBufferAlphaPtr()[s], t * sizeof(u8));
	AreaUp.Scroll(hx, FetchResizedBufferHeight(AreaUp,
		AreaUp.GetHeight()));
	AreaUp.ClearTextLine(0);
	SetCurrentTextLineNOf(AreaUp, 0);

	TextFileBuffer::Iterator itUpOld(itUp);

	itUp = FetchPreviousLineIterator(AreaUp, itUp,
		pText->Blocks.begin());
	PutLine<TextFileBuffer::Iterator, ucs2_t>(AreaUp, itUp, itUpOld);
	itDn = FetchPreviousLineIterator(AreaUp, itDn,
		pText->Blocks.begin());
	Invalidate();
	return true;
}

bool
MDualScreenReader::LineDown()
{
	if(IsTextBottom())
		return false;

	const u8 h = lnHeight, hx = h + GetLineGapUp();
	const SDst w = AreaUp.GetWidth();
	const u32 t = w * h,
		s = AreaUp.Margin.Top * w,
		d = (AreaUp.GetHeight() - FetchResizedMargin(AreaUp,
			AreaUp.GetHeight()) - h) * w;

	AreaUp.Scroll(-hx);
	std::memcpy(&AreaUp.GetBufferPtr()[d],
		&AreaDown.GetBufferPtr()[s], t * sizeof(PixelType));
	std::memcpy(&AreaUp.GetBufferAlphaPtr()[d],
		&AreaDown.GetBufferAlphaPtr()[s], t * sizeof(u8));
	AreaDown.Scroll(-hx);
	AreaDown.ClearTextLineLast();
	AreaDown.SetTextLineLast();
	itDn = PutLine(AreaDown, itDn);
	itUp = FetchNextLineIterator(AreaUp, itUp, pText->Blocks.end());
	Invalidate();
	return true;
}

void
MDualScreenReader::LoadText(TextFile& file)
{
	if(file.IsValid())
	{
		cp = file.GetEncoding();
		pText = ynew BlockedText(file);
		itUp = pText->Blocks.begin();
		itDn = pText->Blocks.end();
		Update();
	}
	else
		PutString(AreaUp, L"文件打开失败！\n");
}

void
MDualScreenReader::PrintTextUp(const Graphics& g_up)
{
	BlitTo(g_up, AreaUp, Point::Zero, Point::Zero, rot);
}

void
MDualScreenReader::PrintTextDown(const Graphics& g_down)
{
	BlitTo(g_down, AreaDown, Point::Zero, Point::Zero, rot);
}

void
MDualScreenReader::Reset()
{
	//清除字符区域缓冲区。
	AreaUp.ClearImage();
	AreaDown.ClearImage();
	//复位缓存区域写入位置。
	AreaUp.ResetPen();
	AreaDown.ResetPen();
}

bool
MDualScreenReader::ScreenUp()
{
	if(IsTextTop())
		return false;
	itUp = FetchPreviousLineIterator(AreaUp, itUp, pText->Blocks.begin(),
		AreaUp.GetTextLineN() + AreaDown.GetTextLineN());
	Update();
	return true;
}
bool
MDualScreenReader::ScreenDown()
{
	if(IsTextBottom())
		return false;

	int t(AreaUp.GetTextLineN() + AreaDown.GetTextLineN());

	while(t-- && itDn != pText->Blocks.end())
	{
		itUp = FetchNextLineIterator(AreaUp, itUp, pText->Blocks.end());
		itDn = FetchNextLineIterator(AreaDown, itDn,
			pText->Blocks.end());
	}
//	itUp = itDn;
	Update();
	return true;
}

/*void
MDualScreenReader::Scroll(Function<void()> pCheck)
{
}*/

void
MDualScreenReader::UnloadText()
{
	itUp = Text::TextFileBuffer::Iterator();
	itDn = Text::TextFileBuffer::Iterator();
	cp = Text::CharSet::Null;
	safe_delete_obj()(pText);
}

void
MDualScreenReader::Update()
{
	Reset();
	//文本填充：输出文本缓冲区字符串，并返回填充字符数。
	itDn = PutString(AreaDown, PutString(AreaUp, itUp));
	Invalidate();
}

YSL_END_NAMESPACE(Components)

YSL_END_NAMESPACE(DS)

YSL_END

