//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ARGUMENTLINETOOL_HPP
#define VICTORIAM_ARGUMENTLINETOOL_HPP

#include <Victoriam/Core/Base.hpp>

VISRCBEG

class cArgumentLineTool
{
	UInt32 Count = {};
	Int8** Args = nullptr;
public:
	VIDECL inline cArgumentLineTool() = default;
	VIDECL inline ~cArgumentLineTool() = default;
	VIDECL inline cArgumentLineTool(Int32 argc, Int8** argv) : Count(argc), Args(argv) {}

	VIDECL inline String operator[](UInt32 n) const
	{
		assert(n < Count);
		return Args[n];
	}
};

VISRCEND

#endif //VICTORIAM_ARGUMENTLINETOOL_HPP
