//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_VULKANIMAGEVIEW_HPP
#define VICTORIAM_VULKANIMAGEVIEW_HPP

#include <Victoriam/Graphics/GImage.hpp>

#include <vulkan/vulkan.h>

VISRCBEG

class VIDECL CVulkanImageView : public CImageView {
	VkImageView m_View;
	PGraphicsContext& m_Context;
public:
	VIDECL  CVulkanImageView(PGraphicsContext& context, const PImage& image, const SImageViewCreateInfo& createInfo);
	VIDECL ~CVulkanImageView() override;

	VIDECL VIREQOUT SImageViewObject GetObject() override;
private:
	void CreateVulkanImageView(const PImage& image, const SImageViewCreateInfo& createInfo);
};

VISRCEND

#endif //VICTORIAM_VULKANIMAGEVIEW_HPP
