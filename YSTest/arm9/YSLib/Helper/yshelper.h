﻿/*
	Copyright (C) by Franksoft 2010.

	This file is part of the YSLib project, and may only be used,
	modified, and distributed under the terms of the YSLib project
	license, LICENSE.TXT.  By continuing to use, modify, or distribute
	this file you indicate that you have read the license and
	understand and accept it fully.
*/

/*!	\file yshelper.h
\ingroup Helper
\brief Shell 助手模块。
\version 0.1864;
\author FrankHB<frankhb1989@gmail.com>
\par 创建时间:
	2010-03-14 14:07:22 + 08:00;
\par 修改时间:
	2010-11-12 18:42 + 08:00;
\par 字符集:
	UTF-8;
\par 模块名称:
	YSLib::Helper::YShellHelper;
*/


#ifndef INCLUDED_YSHELPER_H_
#define INCLUDED_YSHELPER_H_

#include "../ysbuild.h"

YSL_BEGIN

//定义并使用 dynamic_cast 初始化引用。
#define DefDynInitRef(_type, _name, _expr) \
	_type& _name(dynamic_cast<_type&>(_expr));

//句柄语法糖。

/*!
\brief 句柄赋值。
*/
template<class _handle>
inline void
ReplaceHandle(_handle& h, _handle hWnd)
{
	YDelete(h);
	h = hWnd;
}

/*!
\brief 句柄转换：内建指针。
*/
template<class _type, class _handle>
inline _type*
HandleCast(_handle h)
{
	return dynamic_cast<_type*>(GetPointer(h));
}

/*!
ythrow(std::bad_cast)
\brief 句柄转换：对象引用。
*/
template<class _type, class _handle>
inline _type&
HandleToReference(_handle h) ythrow(std::bad_cast)
{
	_type* _tmp(dynamic_cast<_type*>(GetPointer(h)));

	if(!_tmp)
		throw std::bad_cast();
	return *_tmp;
}

/*!
\brief 从指定 Shell 新建窗体。
*/
template<class _type>
HWND NewWindow(HSHL hShl)
{
	return HWND(new _type(HSHL(hShl)));
}


//全局函数。

/*!
\brief 取当前线程空间中运行的 Shell 句柄。
*/
inline HSHL
NowShell()
{
	return theApp.GetShellHandle();
}

/*!
\brief 判断 Shell 句柄是否为当前线程空间中运行的 Shell 句柄。
*/
inline bool
IsNowShell(HSHL hShl)
{
	return theApp.GetShellHandle() == hShl;
}

/*!
\brief 添加 Shell 对象。
*/
inline HSHL
NowShellAdd(HSHL hShl)
{
	if(hShl)
		theApp += *hShl;
	return hShl;
}
/*!
\brief 添加 Shell 对象。
*/
inline HSHL
NowShellAdd(YShell& shl)
{
	theApp += shl;
	return HSHL(&shl);
}

/*!
\brief 向指定 Shell 对象转移线程控制权。
*/
inline ERRNO
NowShellTo(HSHL hShl)
{
	return -!hShl->Activate();
}

/*!
\brief 向新建 Shell 对象转移控制权。
*/
template<class _tShl>
inline ERRNO
NowShellToNew()
{
	return NowShellTo(new _tShl());
}

/*!
\brief 向全局 Shell 管理器的对象转移控制权。
*/
template<class _tShl>
inline ERRNO
NowShellToStored()
{
	return NowShellTo(GStaticCache<_tShl>::GetPointer());
}

/*!
\brief 通过主消息队列向指定 Shell 对象转移控制权。
*/
inline void
SetShellTo(HSHL hShl, Shells::MSGPRIORITY p = 0x80)
{
	InsertMessage(NULL, SM_SET, p, handle_cast<WPARAM>(hShl));
}

/*!
\brief 通过主消息队列向新建 Shell 对象转移控制权。
*/
template<class _tShl>
inline void
SetShellToNew()
{
	SetShellTo(new _tShl());
}

/*!
\brief 通过主消息队列向全局 Shell 管理器内的对象转移控制权。
*/
template<class _tShl>
inline void
SetShellToStored()
{
	SetShellTo(GStaticCache<_tShl>::GetPointer());
}

/*!
\brief 封装向全局 Shell 管理器内的对象转移控制权。
*/
template<class _tShl>
inline void
CallStoredAtOnce()
{
	NowShellToStored<_tShl>();
}

/*!
\brief 封装通过消息队列向全局 Shell 管理器内的对象转移控制权。
*/
template<class _tShl>
inline void
CallStored()
{
	SetShellToStored<_tShl>();
}


//资源相关定义和函数。

YSL_BEGIN_NAMESPACE(Drawing)

typedef void (*PPDRAW)(BitmapPtr, SDST, SDST); //!< 简单屏幕绘图函数指针类型。

/*!
\brief 全屏幕描点。
\note 颜色由坐标决定。
*/
inline void
ScrDraw(BitmapPtr buf, PPDRAW f)
{
	for(SDST y = 0; y < SCRH; ++y)
		for(SDST x = 0; x < SCRW; ++x)
			f(buf, x, y);
}

/*!
\brief 新建屏幕图像。
*/
inline YImage*
NewScrImage(ConstBitmapPtr p)
{
	return new YImage(p, SCRW, SCRH);
}

/*!
\brief 新建屏幕图像并指定绘图函数填充。
*/
YImage*
NewScrImage(PPDRAW f, BitmapPtr gbuf = NULL);

/*!
\brief 使用 new 分配空间并复制无压缩位图。
*/
template<typename _tPixel>
_tPixel*
NewBitmapRaw(const _tPixel* s, std::size_t n)
{
	if(s && n)
	{
		std::size_t size(sizeof(_tPixel) * n);
		_tPixel* d(new _tPixel[size]);

		if(d)
			std::memcpy(d, s, size);
		return d;
	}
	return NULL;
}

YSL_END_NAMESPACE(Drawing)

YSL_END;

#endif

