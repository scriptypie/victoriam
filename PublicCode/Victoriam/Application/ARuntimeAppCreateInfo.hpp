//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ARUNTIMEAPPCREATEINFO_HPP
#define VICTORIAM_ARUNTIMEAPPCREATEINFO_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/Application/AArgumentLineTool.hpp>

VISRCBEG

struct SRuntimeAppCreateInfo
{
	CArgumentLineTool Arguments = {};
	String AppName = {};
	String CWD = {};
};

VISRCEND

#endif //VICTORIAM_ARUNTIMEAPPCREATEINFO_HPP
