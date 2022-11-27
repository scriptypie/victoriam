//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#include <Victoriam/Graphics/GImage.hpp>

#include "VulkanBackend/VulkanImage.hpp"

VISRCBEG

PImage CImage::Create(PGraphicsContext &context, const SImageCreateInfo &createInfo) {
	return FCreateShared<CVulkanImage>(context, createInfo);
}

VISRCEND
