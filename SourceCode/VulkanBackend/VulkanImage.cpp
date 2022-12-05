//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#include "VulkanImage.hpp"
#include "VulkanMemoryBuffer.hpp"

VISRCBEG

CVulkanImage::CVulkanImage(PGraphicsContext &context, const SImageCreateInfo &createInfo) : m_Context(context) {
	m_Extent = createInfo.Extent;
	m_Type = createInfo.Type;

	CreateVulkanImage(createInfo);
	if (createInfo.bCreateView) {
		CreateVulkanImageView(createInfo);
	}
}

CVulkanImage::~CVulkanImage() {
	auto device = Accessors::GraphicsContext::GetDevice(m_Context);
	if (m_View) {
		vkDestroyImageView(device, m_View, nullptr);
		m_View = nullptr;
	}
	if (m_Memory) {
		vkFreeMemory(device, m_Memory, nullptr);
		m_Memory = nullptr;
	}
	if (m_Image) {
		vkDestroyImage(device, m_Image, nullptr);
		m_Image = nullptr;
	}
}

SExtent3D CVulkanImage::GetExtent() const {
	return m_Extent;
}

UInt32 CVulkanImage::GetWidth() const {
	return m_Extent.Width;
}

UInt32 CVulkanImage::GetHeight() const {
	return m_Extent.Height;
}

Signal CVulkanImage::GetType() const {
	return m_Type;
}

void CVulkanImage::CreateVulkanImage(const SImageCreateInfo &createInfo) {
	VkImageCreateInfo imageCreateInfo = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
	imageCreateInfo.imageType     = CCast<VkImageType>(createInfo.Type);
	imageCreateInfo.extent.width  = createInfo.Extent.Width;
	imageCreateInfo.extent.height = createInfo.Extent.Height;
	imageCreateInfo.extent.depth  = createInfo.Extent.Depth;
	imageCreateInfo.mipLevels     = 4; // TODO: mip mapping
	imageCreateInfo.arrayLayers   = 1;
	imageCreateInfo.format        = CCast<VkFormat>(createInfo.Format);
	imageCreateInfo.tiling        = VK_IMAGE_TILING_OPTIMAL;
	imageCreateInfo.usage         = CCast<VkImageUsageFlags>(createInfo.Usage);
	imageCreateInfo.samples       = VK_SAMPLE_COUNT_1_BIT; // TODO: configurable
	imageCreateInfo.sharingMode   = VK_SHARING_MODE_EXCLUSIVE; // TODO: configurable

	VkDeviceSize memoryOffset = 0; // TODO: configurable

	auto fn_CreateImageWithInfo = Accessors::GraphicsContext::CreateImageWithInfo;
	fn_CreateImageWithInfo(m_Context, imageCreateInfo, CCast<VkMemoryPropertyFlags>(createInfo.MemoryType), memoryOffset, m_Image, m_Memory);
}

void CVulkanImage::CreateVulkanImageView(const SImageCreateInfo &createInfo) {
	VkImageViewCreateInfo imageViewCreateInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
	imageViewCreateInfo.image = m_Image;
	auto imageViewType = createInfo.ViewType > 0 ? CCast<VkImageViewType>(createInfo.ViewType - 1) : CCast<VkImageViewType>(createInfo.Type);
	imageViewCreateInfo.viewType = imageViewType;
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

CVulkanImage::CVulkanImage(PGraphicsContext &context, const PPicture &picture, const SImageCreateInfo &createInfo) : m_Context(context) {
	m_Extent = createInfo.Extent;
	m_Type = createInfo.Type;

	CreateVulkanImage(createInfo);
	if (createInfo.bCreateView) {
		CreateVulkanImageView(createInfo);
		if (picture) {
			CopyPictureToImage(picture);
		}
	}
}

void CVulkanImage::SetPicture(const PPicture &picture) {
	CopyPictureToImage(picture);
}

void CVulkanImage::CopyPictureToImage(const PPicture &picture) {
	auto imageBuffer = CCast<VkBuffer>(picture->GetBuffer());
	auto bufferToImage = Accessors::GraphicsContext::CopyBufferToImage;
	bufferToImage(m_Context, imageBuffer, m_Image, m_Extent.Width, m_Extent.Height, 1);
}

VISRCEND
