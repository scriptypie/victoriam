//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_RUNTIMEAPPCREATEINFO_HPP
#define VICTORIAM_RUNTIMEAPPCREATEINFO_HPP

#include <Victoriam/Core/Base.hpp>
#include <Victoriam/Application/ArgumentLineTool.hpp>

VISRCBEG

struct sRuntimeAppCreateInfo
{
	cArgumentLineTool Arguments = {};
	String AppName = {};
	String CWD = {};
};

VISRCEND

#endif //VICTORIAM_RUNTIMEAPPCREATEINFO_HPP
