//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_AVERTEXBUFFER_HPP
#define VICTORIAM_AVERTEXBUFFER_HPP

#include "../VulkanVertexBuffer.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL VertexBuffer
	{
	public:
		VIDECL VIREQOUT inline static VkDescriptorBufferInfo GetDescriptorBufferInfo(const PVertexBuffer& buffer, const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
		{
			return CCast<CVulkanVertexBuffer*>(buffer.get())->GetDescriptorBufferInfo(size, offset);
		}
	};
}

VISRCEND

#endif //VICTORIAM_AVERTEXBUFFER_HPP
