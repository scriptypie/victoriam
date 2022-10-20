//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ENGINEINFO_HPP
#define VICTORIAM_ENGINEINFO_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

struct sEngineInfo
{
    String version;
};

void fGetEngineInfo(sEngineInfo& info);

VISRCEND

#endif //VICTORIAM_ENGINEINFO_HPP
