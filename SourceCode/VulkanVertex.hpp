//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_VULKANVERTEX_HPP
#define VICTORIAM_VULKANVERTEX_HPP

#include <Victoriam/Graphics/Structs/GVertex.hpp>

#include <vulkan/vulkan.h>

VISRCBEG

VIDECL VIREQOUT inline static CList<VkVertexInputBindingDescription> FGetVertexBindingDescriptions()
{
	return {{0, sizeof(SVertex), VK_VERTEX_INPUT_RATE_VERTEX}};
}

VIDECL VIREQOUT inline static CList<VkVertexInputAttributeDescription> FGetVertexAttributeDescriptions()
{
	return
	{
		{ 0, 0, VK_FORMAT_R32G32B32_SFLOAT,    offsetof(SVertex, Position) },
		{ 1, 0, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(SVertex, Color)    },
		{ 2, 0, VK_FORMAT_R32G32B32_SFLOAT,    offsetof(SVertex, Normal)   },
		{ 3, 0, VK_FORMAT_R32G32_SFLOAT,       offsetof(SVertex, UV)       },
	};
}


VISRCEND

#endif //VICTORIAM_VULKANVERTEX_HPP
