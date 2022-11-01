//
// Created by Вячеслав Кривенко on 01.11.2022.
//

#ifndef VICTORIAM_COMPONENTSUN_HPP
#define VICTORIAM_COMPONENTSUN_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>

VISRCBEG

struct VIDECL SComponentSun : SComponentBase
{
	COMPONENT_DECL(ComponentSun)

	SVector3 Direction = {0.0F, 1.0F, 0.0F};

	VIDECL explicit inline SComponentSun(const SVector3& direction) : Direction(direction) {}

};

VISRCEND

#endif //VICTORIAM_COMPONENTSUN_HPP
