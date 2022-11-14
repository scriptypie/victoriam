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

	SVector3 Translation = {};
	Float32  Scale = 1.0F;
	SVector3 Rotation = {};

	VIDECL VIREQOUT inline SMatrix4 Transform() const {
		SMatrix4 rotation = glm::toMat4(glm::quat(FRadians(Rotation)));
		return FTranslate(SMatrix4(1.0f), -Translation)
		       * rotation
		       * FScale(SMatrix4(1.0f), SVector3(Scale));
	}

};

VISRCEND

#endif //VICTORIAM_COMPONENTTRANSFORM_HPP
