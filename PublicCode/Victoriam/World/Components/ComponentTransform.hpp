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
		SMatrix4 transform(1.0);
		transform *= FTranslate(SMatrix4(1.0), Translation);
		transform *= FMatrix4(SQuaternion(FRadians(Rotation)));
		transform *= FScale(SMatrix4(1.0), Scale);
		return transform;
	}

};

VISRCEND

#endif //VICTORIAM_COMPONENTTRANSFORM_HPP
