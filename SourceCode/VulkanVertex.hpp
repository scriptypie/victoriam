//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_VULKANVERTEX_HPP
#define VICTORIAM_VULKANVERTEX_HPP

#include <Victoriam/Graphics/Structs/GVertex.hpp>

#include <vulkan/vulkan.h>

VISRCBEG

VIDECL VIREQOUT inline static List<VkVertexInputBindingDescription> GetVertexBindingDesctiptions()
{
	return {{0, sizeof(sVertex), VK_VERTEX_INPUT_RATE_VERTEX}};
}

VIDECL VIREQOUT inline static List<VkVertexInputAttributeDescription> GetVertexAttributeDescriptions()
{
	List<VkVertexInputAttributeDescription> result(1);
	result[0].binding = 0;
	result[0].location = 0;
	result[0].format = VK_FORMAT_R32G32_SFLOAT;
	result[0].offset = 0;
	return result;
}


VISRCEND

#endif //VICTORIAM_VULKANVERTEX_HPP
