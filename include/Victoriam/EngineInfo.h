//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ENGINEINFO_H
#define VICTORIAM_ENGINEINFO_H

#include <Victoriam/Core/Base.h>

VISRCBEG

struct sEngineInfo
{
    String version;
};

void fGetEngineInfo(sEngineInfo& info);

VISRCEND

#endif //VICTORIAM_ENGINEINFO_H
