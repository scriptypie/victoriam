//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>

#include "VulkanDescriptorSetLayout.hpp"

VISRCBEG

PDescriptorSetLayout CDescriptorSetLayout::Create(PGraphicsContext &context, const SDescriptorSetLayoutCreateInfo &createInfo)
{
	return CreateUPtr<CVulkanDescriptorSetLayout>(context, createInfo);
}

VISRCEND