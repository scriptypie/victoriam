//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#include <Victoriam/Graphics/GImageView.hpp>

#include "VulkanBackend/VulkanImageView.hpp"

VISRCBEG

PImageView CImageView::Create(PGraphicsContext &context, const PImage &image, const SImageViewCreateInfo &createInfo) {
	return FCreateShared<CVulkanImageView>(context, image, createInfo);
}

VISRCEND
