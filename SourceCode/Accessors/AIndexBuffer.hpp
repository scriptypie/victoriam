//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_AINDEXBUFFER_HPP
#define VICTORIAM_AINDEXBUFFER_HPP

#include "../VulkanBackend/VulkanIndexBuffer.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL IndexBuffer {
	public:
	VIDECL VIREQOUT inline static VkDescriptorBufferInfo GetDescriptorBufferInfo(const PIndexBuffer& buffer, const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {}) {
			return CCast<CVulkanIndexBuffer*>(buffer.get())->GetDescriptorBufferInfo(size, offset);
		}
	};
}

VISRCEND


#endif //VICTORIAM_AINDEXBUFFER_HPP
