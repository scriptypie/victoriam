//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_AIMAGE_HPP
#define VICTORIAM_AIMAGE_HPP

#include "../VulkanBackend/VulkanImage.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL Image {
	public:
		VIDECL VIREQOUT inline static VkImage GetImage(const PImage& image) {
			return CCast<CVulkanImage*>(image.Get())->GetImage();
		}
		VIDECL VIREQOUT inline static VkImageView GetImageView(const PImage& image) {
			return CCast<CVulkanImage*>(image.Get())->GetImageView();
		}
		VIDECL VIREQOUT inline static VkDeviceMemory GetImageMemory(const PImage& image) {
			return CCast<CVulkanImage*>(image.Get())->GetImageMemory();
		}
	};

}

VISRCEND

#endif //VICTORIAM_AIMAGE_HPP
