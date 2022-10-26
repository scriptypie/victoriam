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

	SVector3 Translation;
	SVector3 Scale = { 1.0F, 1.0F, 1.0F };
	SVector3 Rotation; // YXZ

	VIDECL VIREQOUT SMatrix4 Transform() const
	{
		auto transform = glm::translate(SMatrix4{1.0F}, Translation);
		transform = glm::rotate(transform, Rotation.y, SVector3(0.0F, 1.0F, 0.0F));
		transform = glm::rotate(transform, Rotation.x, SVector3(1.0F, 0.0F, 0.0F));
		transform = glm::rotate(transform, Rotation.z, SVector3(0.0F, 0.0F, 1.0F));
		transform = glm::scale(transform, Scale);
		return transform;
	}

};

VISRCEND

#endif //VICTORIAM_COMPONENTTRANSFORM_HPP
