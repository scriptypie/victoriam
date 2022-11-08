//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_ABUFFER_HPP
#define VICTORIAM_ABUFFER_HPP

#include "../VulkanBuffer.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL Buffer
	{
	public:
		VIDECL VIREQOUT inline static VkDescriptorBufferInfo GetDescriptorBufferInfo(const PBuffer& buffer, const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
		{
			return CCast<CVulkanBuffer*>(buffer.get())->GetDescriptorBufferInfo(size, offset);
		}
		VIDECL VIREQOUT inline static VkDescriptorBufferInfo GetDescriptorBufferInfo(const PUniformBuffer& uniformBuffer, const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
		{
			return CCast<CVulkanBuffer*>(uniformBuffer.get())->GetDescriptorBufferInfo(size, offset);
		}
	};
}

VISRCEND

#endif //VICTORIAM_ABUFFER_HPP
