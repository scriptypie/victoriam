//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#include <Victoriam/Graphics/GImage.hpp>

#include "VulkanBackend/VulkanImage.hpp"

VISRCBEG

PImage CImage::Create2D(PGraphicsContext &context, const SImageCreateInfo &createInfo) {
	return CreateSPtr<CVulkanImage>(context, createInfo);
}

VISRCEND
