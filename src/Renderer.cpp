//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include<Victoriam/Graphics/Renderer.hpp>

#include "VulkanRenderer.hpp"

VISRCBEG

pRenderer cRenderer::Create(const sRendererCreateInfo &createInfo)
{
	return CreateUPtr<cVulkanRenderer>(createInfo);
}

VISRCEND
