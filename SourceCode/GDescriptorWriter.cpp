//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#include <Victoriam/Graphics/GDescriptorWriter.hpp>

#include "VulkanBackend/VulkanDescriptorWriter.hpp"

VISRCBEG

PDescriptorWriter CDescriptorWriter::Create(PDescriptorPool &pool, PDescriptorSetLayout &layout)
{
	return FCreateShared<CVulkanDescriptorWriter>(pool, layout);
}

VISRCEND
