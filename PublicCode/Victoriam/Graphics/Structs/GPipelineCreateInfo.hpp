//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GPIPELINECREATEINFO_HPP
#define VICTORIAM_GPIPELINECREATEINFO_HPP

#include "Victoriam/Graphics/Basics.hpp"
#include "Victoriam/Math/MVector2.hpp"

VISRCBEG

struct sPipelineCreateInfo
{
	VIDECL UInt32 Width;
	VIDECL UInt32 Height;

	VIDECL inline explicit sPipelineCreateInfo(const Vector2& resolution) : sPipelineCreateInfo(CCast<UInt32>(resolution.x), CCast<UInt32>(resolution.y))
	{}
	inline sPipelineCreateInfo(const UInt32& width, const UInt32& height)
	{
		Width = width;
		Height = height;
	}
};

VISRCEND

#endif //VICTORIAM_GPIPELINECREATEINFO_HPP
