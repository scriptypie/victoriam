//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#include <Victoriam/Graphics/GImage.hpp>
#include "VulkanBackend/VulkanImage.hpp"

VISRCBEG

PImage CImage::Create(PGraphicsContext &context, const SImageCreateInfo &createInfo) {
	return FMakeShared<CVulkanImage>(context, createInfo);
}

PImage CImage::Create(PGraphicsContext &context, const PPicture &picture, const SImageCreateInfo &createInfo) {
	return FMakeShared<CVulkanImage>(context, picture, createInfo);
}

VISRCEND
