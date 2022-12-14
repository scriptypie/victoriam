//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AARGUMENTLINETOOL_HPP
#define VICTORIAM_AARGUMENTLINETOOL_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

/**
 * Simple CLTool for getting command line arguments.
 */
class VIDECL CArgumentLineTool
{
	UInt32 m_Count = {};
	Int8** m_Args = nullptr;
public:
	VIDECL inline CArgumentLineTool() = default;
	VIDECL inline ~CArgumentLineTool() = default;
	VIDECL inline CArgumentLineTool(Int32 argc, Int8** argv) : m_Count(argc), m_Args(argv) {}

	VIDECL VIREQOUT inline String operator[](UInt32 n) const
	{
		assert(n < m_Count);
		return m_Args[n];
	}
	VIDECL VIREQOUT inline UInt32 Count() const {
		return m_Count;
	}
};

VISRCEND

#endif //VICTORIAM_AARGUMENTLINETOOL_HPP
