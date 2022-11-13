//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/GGraphicsContext.hpp>

#include "VulkanBackend/VulkanGraphicsContext.hpp"

VISRCBEG

PGraphicsContext CGraphicsContext::Create(const SPtr<CWindow> &window) {
	return CreateSPtr<CVulkanGraphicsContext>(window);
}

VISRCEND

