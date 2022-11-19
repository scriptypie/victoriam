//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#include "VulkanImageView.hpp"

#include "../Accessors/AGraphicsContext.hpp"
#include "../Accessors/AImage.hpp"

VISRCBEG

CVulkanImageView::CVulkanImageView(PGraphicsContext &context, const PImage &image, const SImageViewCreateInfo &createInfo) : m_Context(context) {
	CreateVulkanImageView(image, createInfo);
}

CVulkanImageView::~CVulkanImageView() {
	auto device = Accessors::GraphicsContext::GetDevice(m_Context);
	if (m_View) {
		vkDestroyImageView(device, m_View, nullptr);
		m_View = nullptr;
	}
}

void CVulkanImageView::CreateVulkanImageView(const PImage &image, const SImageViewCreateInfo &createInfo) {
	VkImageViewCreateInfo imageViewCreateInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
	imageViewCreateInfo.image = Accessors::Image::GetImage(image);
	imageViewCreateInfo.viewType = CCast<VkImageViewType>(createInfo.ViewType - 1);
	imageViewCreateInfo.format = CCast<VkFormat>(createInfo.Format);
	imageViewCreateInfo.subresourceRange.aspectMask = CCast<VkImageAspectFlags>(createInfo.Aspect);

	// TODO: configurable:
	imageViewCreateInfo.subresourceRange.levelCount = 1;
	imageViewCreateInfo.subresourceRange.layerCount = 1;
	imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	imageViewCreateInfo.subresourceRange.baseMipLevel = 0;

	auto device = Accessors::GraphicsContext::GetDevice(m_Context);

	if (vkCreateImageView(device, &imageViewCreateInfo, nullptr, &m_View) != VK_SUCCESS)
	ViAbort("Failed to create image view!");
}

	SImageViewObject CVulkanImageView::GetObject() {
		return CCast<SImageViewObject>(m_View);
	}

VISRCEND
