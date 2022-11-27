//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ENGINEINFO_HPP
#define VICTORIAM_ENGINEINFO_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

struct VIDECL SEngineInfo
{
    StringView Version;
	StringView Owner;
};

VIDECL void FGetEngineInfo(SEngineInfo& info);

VISRCEND

#endif //VICTORIAM_ENGINEINFO_HPP
