//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_COMPONENTTRANSFORM_HPP
#define VICTORIAM_COMPONENTTRANSFORM_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>

VISRCBEG

struct VIDECL SComponentTransform : SComponentBase
{
	COMPONENT_DECL(ComponentTransform)

	SVector2 Translation;
	SVector2 Scale = { 1.0F, 1.0F };

	SMatrix2 Transform()
	{
		SMatrix2 scalemat = { { Scale.x, 0.0f },
		                       { 0.0f, Scale.y } };

		return scalemat;
	}

};

VISRCEND

#endif //VICTORIAM_COMPONENTTRANSFORM_HPP
