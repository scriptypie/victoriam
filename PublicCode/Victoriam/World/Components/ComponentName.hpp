//
// Created by Вячеслав Кривенко on 26.10.2022.
//

#ifndef VICTORIAM_COMPONENTNAME_HPP
#define VICTORIAM_COMPONENTNAME_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>

VISRCBEG

struct VIDECL SComponentName : SComponentBase
{
	COMPONENT_DECL(ComponentName)

	String Name;

};

VISRCEND

#endif //VICTORIAM_COMPONENTNAME_HPP
