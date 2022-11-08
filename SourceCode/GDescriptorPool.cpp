//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#include <Victoriam/Graphics/GDescriptorPool.hpp>

#include "VulkanDescriptorPool.hpp"

VISRCBEG

PDescriptorPool CDescriptorPool::Create(PGraphicsContext& context, const SDescriptorPoolCreateInfo& createInfo)
{
	return CreateUPtr<CVulkanDescriptorPool>(context, createInfo);
}

VISRCEND
