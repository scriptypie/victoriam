//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#include <Victoriam/Graphics/GDescriptorPool.hpp>

#include "VulkanBackend/VulkanDescriptorPool.hpp"

VISRCBEG

PDescriptorPool CDescriptorPool::Create(PGraphicsContext& context, const SDescriptorPoolCreateInfo& createInfo)
{
	return FCreateUnique<CVulkanDescriptorPool>(context, createInfo);
}

VISRCEND
