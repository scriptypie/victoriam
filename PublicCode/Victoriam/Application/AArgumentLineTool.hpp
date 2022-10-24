//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AARGUMENTLINETOOL_HPP
#define VICTORIAM_AARGUMENTLINETOOL_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

class CArgumentLineTool
{
	UInt32 Count = {};
	Int8** Args = nullptr;
public:
	VIDECL inline CArgumentLineTool() = default;
	VIDECL inline ~CArgumentLineTool() = default;
	VIDECL inline CArgumentLineTool(Int32 argc, Int8** argv) : Count(argc), Args(argv) {}

	VIDECL inline String operator[](UInt32 n) const
	{
		assert(n < Count);
		return Args[n];
	}
};

VISRCEND

#endif //VICTORIAM_AARGUMENTLINETOOL_HPP
