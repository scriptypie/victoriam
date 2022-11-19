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
			return CCast<CVulkanImage*>(image.get())->GetImage();
		}
		VIDECL VIREQOUT inline static VkDeviceMemory GetImageMemory(const PImage& image) {
			return CCast<CVulkanImage*>(image.get())->GetImageMemory();
		}
	};

}

VISRCEND

#endif //VICTORIAM_AIMAGE_HPP
