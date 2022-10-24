//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#ifndef VICTORIAM_CFLAGS_HPP
#define VICTORIAM_CFLAGS_HPP

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

VIDECL typedef unsigned long long FlagDef;

struct VIDECL SFlags
{
	FlagDef _base_;

	SFlags() : _base_(0x0000000000000000) {}
	explicit SFlags(const FlagDef& f) : _base_(f) {}

	VIDECL void operator+=(const FlagDef& f)
	{
		_base_ |= f;
	}
	VIDECL bool operator==(const FlagDef& f) const
	{
		return (_base_ & f) == f;
	}
	VIDECL VIREQOUT bool Contains(const FlagDef& f) const
	{
		return *this == f;
	}
};

VISRCEND

#endif //VICTORIAM_CFLAGS_HPP
