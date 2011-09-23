﻿/*
	Copyright (C) by Franksoft 2009 - 2011.

	This file is part of the YSLib project, and may only be used,
	modified, and distributed under the terms of the YSLib project
	license, LICENSE.TXT.  By continuing to use, modify, or distribute
	this file you indicate that you have read the license and
	understand and accept it fully.
*/

/*!	\file chrdef.h
\ingroup CHRLib CHRLib 库
\brief CHRLib 类型定义。
\version r1594;
\author FrankHB<frankhb1989@gmail.com>
\par 创建时间:
	2009-11-17 17:52:35 +0800;
\par 修改时间:
	2011-09-21 07:40 +0800;
\par 字符集:
	UTF-8;
\par 模块名称:
	CHRLib::CHRDefinition;
*/


#ifndef CHRLIB_INC_CHRDEF_H_
#define CHRLIB_INC_CHRDEF_H_

#include <ydef.h>

#define CHRLIB_BEGIN	namespace CHRLib {
#define CHRLIB_END		}
#define CHRLIB_			::CHRLib::
#define CHRLIB			::CHRLib

#define CHRLIB_BEGIN_NAMESPACE(s)	namespace s {
#define CHRLIB_END_NAMESPACE(s)	}

CHRLIB_BEGIN

using ystdex::byte;

typedef unsigned char ubyte_t;
typedef unsigned long usize_t;

// 字符类型定义。
typedef std::uint16_t ucs2_t; //!< UCS-2 字符类型。
typedef std::uint32_t ucs4_t; //!< UCS-4 字符类型。
typedef std::int_least32_t ucsint_t; //!< UCS 字符对应的整数类型。

/*!
\brief 宽字符串转换宏。
*/
#define _ustr(str) reinterpret_cast<const CHRLib::ucs4_t*>(L##str)

CHRLIB_END

#endif

