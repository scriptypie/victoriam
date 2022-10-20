//
// Created by Вячеслав Кривенко on 20.10.2022.
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
		VIDECL inline static void Bind(const pVertexBuffer& vertexBuffer, const VkCommandBuffer& buffer)
		{
			CCast<cVulkanVertexBuffer*>(vertexBuffer.get())->Bind(buffer);
		}
		VIDECL inline static void Draw(const pVertexBuffer& vertexBuffer, const VkCommandBuffer& buffer)
		{
			CCast<cVulkanVertexBuffer*>(vertexBuffer.get())->Draw(buffer);
		}
	};

}

VISRCEND

#endif //VICTORIAM_AVERTEXBUFFER_HPP
