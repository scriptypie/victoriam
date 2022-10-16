//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_PIPELINECREATEINFO_HPP
#define VICTORIAM_PIPELINECREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Math/Vector2.hpp>

VISRCBEG

enum class ecPrimitiveTopology : UInt32
{
	None                  VIDECL = 0,
	TopologyDefault       VIDECL = 3,
	TopologyTriangleList  VIDECL = 3,
	TopologyTriangleStrip VIDECL = 4
};

struct VIDECL sPipelineInputAssemblyCreateInfo
{
	VIDECL ecPrimitiveTopology Topology = ecPrimitiveTopology::TopologyDefault;
};

struct sPipelineCreateInfo
{
	VIDECL UInt32 Width;
	VIDECL UInt32 Height;
	VIDECL UInt32 InputAssemblyCreateInfo = {};

	VIDECL inline explicit sPipelineCreateInfo(const Vector2& resolution) : sPipelineCreateInfo(CCast<UInt32>(resolution.x), CCast<UInt32>(resolution.y))
	{}
	inline sPipelineCreateInfo(const UInt32& width, const UInt32& height)
	{
		Width = width;
		Height = height;
	}
};

VISRCEND

#endif //VICTORIAM_PIPELINECREATEINFO_HPP
