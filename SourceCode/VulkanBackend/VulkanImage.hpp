//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_VULKANIMAGE_HPP
#define VICTORIAM_VULKANIMAGE_HPP

#include <Victoriam/Graphics/GImage.hpp>
#include <Victoriam/Graphics/GPicture.hpp>

#include <vulkan/vulkan.h>

VISRCBEG

namespace Accessors { class Image; }

class VIDECL CVulkanImage : public CImage {
	friend class Accessors::Image;
	PGraphicsContext& m_Context;
	SExtent3D m_Extent = {};
	VkImage m_Image = {};
	VkDeviceMemory m_Memory = {};
	VkImageView m_View = {};
	Signal m_Type = {};
public:
	VIDECL  CVulkanImage(PGraphicsContext& context, const SImageCreateInfo& createInfo);
	VIDECL  CVulkanImage(PGraphicsContext &context, const PPicture &picture, const SImageCreateInfo &createInfo);
	VIDECL ~CVulkanImage() override;

	VIDECL VIREQOUT SExtent3D GetExtent() const override;
	VIDECL VIREQOUT UInt32    GetWidth()  const override;
	VIDECL VIREQOUT UInt32    GetHeight() const override;
	VIDECL VIREQOUT Signal    GetType()   const override;
	VIDECL void SetPicture(const PPicture& picture) override;

private:
	void CreateVulkanImage(const SImageCreateInfo& createInfo);
	void CreateVulkanImageView(const SImageCreateInfo& createInfo);
	void CopyPictureToImage(const PPicture& picture);
private:
	VIDECL VIREQOUT inline VkImage GetImage() { return m_Image; }
	VIDECL VIREQOUT inline VkImageView GetImageView() { return m_View; }
	VIDECL VIREQOUT inline VkDeviceMemory GetImageMemory() { return m_Memory; }
};

VISRCEND

#endif //VICTORIAM_VULKANIMAGE_HPP
