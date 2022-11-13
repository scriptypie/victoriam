//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_AUNIFORMBUFFER_HPP
#define VICTORIAM_AUNIFORMBUFFER_HPP

#include "../VulkanBackend/VulkanUniformBuffer.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL UniformBuffer
	{
	public:
		VIDECL VIREQOUT inline static VkDescriptorBufferInfo GetDescriptorBufferInfo(const PUniformBuffer& buffer, const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
		{
			return CCast<CVulkanUniformBuffer*>(buffer.get())->GetDescriptorBufferInfo(size, offset);
		}
	};
}

VISRCEND

#endif //VICTORIAM_AUNIFORMBUFFER_HPP
