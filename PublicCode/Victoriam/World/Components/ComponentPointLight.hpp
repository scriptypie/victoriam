//
// Created by Вячеслав Кривенко on 08.11.2022.
//

#ifndef VICTORIAM_COMPONENTPOINTLIGHT_HPP
#define VICTORIAM_COMPONENTPOINTLIGHT_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>

VISRCBEG

struct VIDECL SComponentPointLight : SComponentBase
{
	COMPONENT_DECL(ComponentPointLight)

	SVector4 LightColor{1.0F}; // W component is intensity

};

VISRCEND

#endif //VICTORIAM_COMPONENTPOINTLIGHT_HPP
