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
		const Float32 c3 = glm::cos(Rotation.z);
		const Float32 s3 = glm::sin(Rotation.z);
		const Float32 c2 = glm::cos(Rotation.x);
		const Float32 s2 = glm::sin(Rotation.x);
		const Float32 c1 = glm::cos(Rotation.y);
		const Float32 s1 = glm::sin(Rotation.y);
		return glm::mat4{
				{
						Scale.x * (c1 * c3 + s1 * s2 * s3),
						Scale.x * (c2 * s3),
						Scale.x * (c1 * s2 * s3 - c3 * s1),
						0.0F,
				},
				{
						Scale.y * (c3 * s1 * s2 - c1 * s3),
						Scale.y * (c2 * c3),
						Scale.y * (c1 * c3 * s2 + s1 * s3),
						0.0F,
				},
				{
						Scale.z * (c2 * s1),
						Scale.z * (-s2),
						Scale.z * (c1 * c2),
						0.0F,
				},
				{Translation.x, Translation.y, Translation.z, 1.0F}};	}

};

VISRCEND

#endif //VICTORIAM_COMPONENTTRANSFORM_HPP
