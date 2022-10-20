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

	inline sPipelineCreateInfo()
	{
	}
};

VISRCEND

#endif //VICTORIAM_GPIPELINECREATEINFO_HPP
