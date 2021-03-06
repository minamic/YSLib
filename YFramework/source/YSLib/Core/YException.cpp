﻿/*
	© 2010-2016 FrankHB.

	This file is part of the YSLib project, and may only be used,
	modified, and distributed under the terms of the YSLib project
	license, LICENSE.TXT.  By continuing to use, modify, or distribute
	this file you indicate that you have read the license and
	understand and accept it fully.
*/

/*!	\file YException.cpp
\ingroup Core
\brief 异常处理模块。
\version r381
\author FrankHB <frankhb1989@gmail.com>
\since 早于 build 132
\par 创建时间:
	2010-06-15 20:30:14 +0800
\par 修改时间:
	2016-08-28 15:29 +0800
\par 文本编码:
	UTF-8
\par 模块名称:
	YSLib::Core::YException
*/


#include "YSLib/Core/YModules.h"
#include YFM_YSLib_Core_YException
#include <ystdex/exception.h> // for ystdex::handle_nested;

namespace YSLib
{

LoggedEvent::LoggedEvent(const char* str, RecordLevel lv)
	: GeneralEvent(Nonnull(str)),
	level(lv)
{}
LoggedEvent::LoggedEvent(string_view sv, RecordLevel lv)
	: GeneralEvent(std::string(sv)),
	level(lv)
{}
LoggedEvent::LoggedEvent(const GeneralEvent& e, RecordLevel lv)
	: GeneralEvent(e),
	level(lv)
{}
ImplDeDtor(LoggedEvent)


FatalError::FatalError(const char* t, string_view c)
	: GeneralEvent(Nonnull(t)),
	content((Nonnull(c.data()), make_shared<string>(string(c))))
{}
ImplDeDtor(FatalError)


void
TraceException(const char* str, RecordLevel lv, size_t level) ynothrow
{
	TryExpr(
		YF_TraceRaw(lv, "%s%s", std::string(level, ' ').c_str(), Nonnull(str)))
	CatchExpr(..., YF_TraceRaw(Critical, "Failure @ TraceException."))
}

void
TraceExceptionType(const std::exception& e, RecordLevel lv) ynothrow
{
	YF_TraceRaw(lv, "Caught std::exception[%s].", typeid(e).name());
}

void
ExtractAndTrace(const std::exception& e, RecordLevel lv) ynothrow
{
	TraceExceptionType(e, lv);
	ExtractException(TraceException, e, lv);
}

void
ExtractException(const ExtractedLevelPrinter& print, const std::exception& e,
	RecordLevel lv, size_t level) ynothrow
{
	TryExpr(print(e.what(), lv, level))
	CatchExpr(..., print("Exception occurred when printing @ ExtractException.",
		Critical, level))
	TryExpr(ystdex::handle_nested(e,
		[&, lv, level](std::exception& ex) ynothrow{
		ExtractException(print, ex, lv, level + 1);
	}))
	CatchExpr(..., print("Unknown nested exception found nested on calling"
		" ystdex::handle_nested @ ExtractException.", Critical, level))
}

bool
TryExecute(std::function<void()> f, const char* desc, RecordLevel lv,
	ExceptionTracer trace)
{
	try
	{
		TryExpr(f())
		catch(...)
		{
			if(desc)
				YF_TraceRaw(Notice, "Exception filtered: %s.", desc);
			throw;
		}
		return {};
	}
	CatchExpr(std::exception& e, trace(e, lv))
	return true;
}

} // namespace YSLib;

