//
// Created by Вячеслав Кривенко on 26.10.2022.
//

#ifndef VICTORIAM_COMPONENTCAMERA_HPP
#define VICTORIAM_COMPONENTCAMERA_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>
#include <Victoriam/Graphics/GCamera.hpp>

VISRCBEG

struct SComponentCamera : SComponentBase
{
	COMPONENT_DECL(ComponentCamera)

	CCamera Camera;
	Bool Primary = true;

};

VISRCEND

#endif //VICTORIAM_COMPONENTCAMERA_HPP
