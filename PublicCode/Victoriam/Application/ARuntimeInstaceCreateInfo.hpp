//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ARUNTIMEINSTACECREATEINFO_HPP
#define VICTORIAM_ARUNTIMEINSTACECREATEINFO_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/Application/AArgumentLineTool.hpp>

VISRCBEG

struct VIDECL SRuntimeInstanceCreateInfo
{
	CArgumentLineTool Arguments = {};
	String AppName = {};
	String CWD = {};
};

VISRCEND

#endif //VICTORIAM_ARUNTIMEINSTACECREATEINFO_HPP
