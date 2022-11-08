//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include <Victoriam/Graphics/GRenderer.hpp>

#include "VulkanRenderer.hpp"

VISRCBEG

PRenderer CRenderer::Create(const SRendererCreateInfo &createInfo)
{
	return CreateUPtr<CVulkanRenderer>(createInfo);
}

VISRCEND
