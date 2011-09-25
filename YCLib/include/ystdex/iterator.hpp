﻿/*
	Copyright (C) by Franksoft 2011.

	This file is part of the YSLib project, and may only be used,
	modified, and distributed under the terms of the YSLib project
	license, LICENSE.TXT.  By continuing to use, modify, or distribute
	this file you indicate that you have read the license and
	understand and accept it fully.
*/

/*!	\file iterator.hpp
\ingroup YCLib
\brief C++ 标准库迭代器扩展。
\version r1321;
\author FrankHB<frankhb1989@gmail.com>
\par 创建时间:
	2011-01-27 23:01:00 +0800;
\par 修改时间:
	2011-09-23 18:51 +0800;
\par 字符集:
	UTF-8;
\par 模块名称:
	YCLib::YStandardExtend::Iterator;
*/


#ifndef YCL_INC_YSTDEX_ITERATOR_HPP_
#define YCL_INC_YSTDEX_ITERATOR_HPP_

#include "../ydef.h"
#include <iterator>
#include <utility>

namespace ystdex
{
	/*!	\defgroup iterators Iterators
	\brief 迭代器。
	*/

	/*!	\defgroup iterator_adaptors Iterator Adaptors
	\ingroup iterators
	\brief 迭代器适配器。
	*/

	/*!
	\ingroup iterator_adaptors
	\brief 伪迭代器。

	总是返回单一值的迭代器适配器。
	*/
	template<typename _type, typename _tIterator = _type*,
		typename _tTraits = std::iterator_traits<_tIterator>>
	class pseudo_iterator : public std::iterator<
		typename _tTraits::iterator_category,
		typename _tTraits::value_type,
		typename _tTraits::difference_type,
		typename _tTraits::pointer,
		typename _tTraits::reference>
	{
	protected:
		typedef _tTraits traits_type;

	public:
		typedef _tIterator iterator_type;
		typedef typename traits_type::iterator_category iterator_category;
		typedef typename traits_type::value_type value_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::reference reference;
		typedef typename traits_type::pointer pointer;

		value_type value;

		yconstexprf
		pseudo_iterator()
			: value()
		{}
		explicit yconstexprf
		pseudo_iterator(value_type v)
			: value(v)
		{}
		yconstexprf inline
		pseudo_iterator(const pseudo_iterator&) = default;
		yconstexprf inline
		pseudo_iterator(pseudo_iterator&&) = default;

		pseudo_iterator&
		operator=(const pseudo_iterator&) = default;
		pseudo_iterator&
		operator=(pseudo_iterator&&) = default;

		//前向迭代器需求。
		yconstexprf reference
		operator*() const
		{
			return value;
		}

		yconstexprf pointer
		operator->() const
		{
			return this;
		}

		pseudo_iterator&
		operator++()
		{
			return *this;
		}

		pseudo_iterator
		operator++(int)
		{
			return *this;
		}

		//双向迭代器需求。
		yconstexprf pseudo_iterator&
		operator--()
		{
			return *this;
		}

		yconstexprf pseudo_iterator
		operator--(int)
		{
			return *this;
		}

		//随机访问迭代器需求。
		yconstexprf reference
		operator[](const difference_type& _n) const
		{
			return this[_n];
		}

		pseudo_iterator&
		operator+=(const difference_type& _n)
		{
			return *this;
		}

		yconstexprf pseudo_iterator
		operator+(const difference_type& _n) const
		{
			return *this;
		}

		yconstexprf pseudo_iterator&
		operator-=(const difference_type& _n)
		{
			return *this;
		}

		yconstexprf pseudo_iterator
		operator-(const difference_type& _n) const
		{
			return *this;
		}
	};


	/*!
	\ingroup iterator_adaptors
	\brief 成对迭代器。

	拼接两个迭代器对得到的迭代器适配器，以第一个为主迭代器的迭代器适配器。
	*/
	template<typename _tMaster, typename _tSlave,
		class _tTraits = std::iterator_traits<_tMaster>>
	class pair_iterator : std::iterator<
		typename _tTraits::iterator_category,
		typename _tTraits::value_type,
		typename _tTraits::difference_type,
		typename _tTraits::pointer,
		typename _tTraits::reference>,
		protected std::pair<_tMaster, _tSlave>
	{
	protected:
		typedef _tTraits traits_type;

	public:
		typedef std::pair<_tMaster, _tSlave> pair_type;
		typedef _tMaster iterator_type;
		typedef typename traits_type::iterator_category iterator_category;
		typedef typename traits_type::value_type value_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::reference reference;
		typedef typename traits_type::pointer pointer;

		yconstexprf
		pair_iterator()
			: std::pair<_tMaster, _tSlave>(_tMaster(), _tSlave())
		{}
		explicit yconstexprf
		pair_iterator(const _tMaster& _i)
			: std::pair<_tMaster, _tSlave>(_i, _tSlave())
		{}
		yconstexprf
		pair_iterator(const _tMaster& _i, const _tSlave& _s)
			: std::pair<_tMaster, _tSlave>(_i, _s)
		{}
		yconstexprf
		pair_iterator(const pair_iterator&) = default;
		yconstexprf
		pair_iterator(pair_iterator&& _r)
			: std::pair<_tMaster, _tSlave>(std::move(_r))
		{}

		inline pair_iterator&
		operator=(const pair_iterator&) = default;
		inline pair_iterator&
		operator=(pair_iterator&&) = default;
		// TODO: Allow iterator to const_iterator conversion;
/*		template<typename _tIter>
		pair_iterator(const pair_iterator<_Iter,
			typename __enable_if<
			(std::__are_same<_Iter, typename _Container::pointer>::__value),
			_Container>::__type>& __i)
			: _M_current(__i.base())
		{}
*/

		//前向迭代器需求。
		yconstexprf reference
		operator*() const
		{
			return *this->first;
		}

		yconstexprf pointer
		operator->() const
		{
			return this->first;
		}

		pair_iterator&
		operator++()
		{
			++this->first;
			++this->second;
			return *this;
		}

		pair_iterator
		operator++(int)
		{
			const auto i(*this);

			++*this;
			return i;
		}

		//双向迭代器需求。
		pair_iterator&
		operator--()
		{
			--this->second;
			--this->first;
			return *this;
		}

		pair_iterator
		operator--(int)
		{
			const auto i(*this);

			--*this;
			return i;
		}

		//随机访问迭代器需求。
		yconstexprf reference
		operator[](const difference_type& _n) const
		{
			return this->first[_n];
		}

		pair_iterator&
		operator+=(const difference_type& _n)
		{
			this->first += _n;
			this->second += _n;
			return *this;
		}

		yconstexprf pair_iterator
		operator+(const difference_type& _n) const
		{
			return pair_iterator(this->first + _n, this->second + _n);
		}

		pair_iterator&
		operator-=(const difference_type& _n)
		{
			this->second -= _n;
			this->first -= _n;
			return *this;
		}

		yconstexprf pair_iterator
		operator-(const difference_type& _n) const
		{
			return pair_iterator(this->first - _n, this->second - _n);
		}

		yconstexprf const pair_type&
		base() const
		{
			return *this;
		}
	};
}

#endif

