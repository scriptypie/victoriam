//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_COMPONENTTRANSFORM_HPP
#define VICTORIAM_COMPONENTTRANSFORM_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>

#include <Victoriam/Math/MVector2.hpp>
#include <Victoriam/Math/MMatrix4.hpp>

VISRCBEG

struct SComponentTransform : public SComponentBase
{
	friend class CGameObject;
	inline static UInt32 GetStaticComponentID() { return 2; }
	UInt32 GetComponentID() override { return GetStaticComponentID(); }

	SVector2 Translation;
	SVector2 Scale = { 1.0F, 1.0F };

	SMatrix4 Transform()
	{
		SMatrix4 scalemat = { Scale.x, 0.0f, 0.0f, 0.0f,
							  0.0f, Scale.y, 0.0f, 0.0f,
							  0.0f, 0.0f,    1.0f, 0.0f,
							  0.0f, 0.0f,    0.0f, 1.0f};
		return scalemat;
	}

};

VISRCEND

#endif //VICTORIAM_COMPONENTTRANSFORM_HPP
