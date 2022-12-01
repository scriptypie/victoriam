//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include <Victoriam/Graphics/GUniformBuffer.hpp>

#include "VulkanBackend/VulkanUniformBuffer.hpp"

VISRCBEG

PUniformBuffer CUniformBuffer::Create(PGraphicsContext& context, const UInt32& count) {
	return FMakeUnique<CVulkanUniformBuffer>(context, count);
}

VISRCEND
