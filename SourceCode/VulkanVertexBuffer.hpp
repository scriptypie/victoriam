//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_VULKANVERTEXBUFFER_HPP
#define VICTORIAM_VULKANVERTEXBUFFER_HPP

#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "Accessors/ADevice.hpp"

VISRCBEG

namespace Accessors { class VertexBuffer; }

class VIDECL cVulkanVertexBuffer : public cVertexBuffer
{
	friend class Accessors::VertexBuffer;

	pDevice& m_Device;
	VkBuffer m_VertexBuffer = {};
	VkDeviceMemory m_VertexBufferMemory = {};
	UInt64 m_VertexCount = {};

public:
	cVulkanVertexBuffer(pDevice& device, const List<sVertex>& vertices);
	~cVulkanVertexBuffer() override;
private:
	void Bind(const VkCommandBuffer& buffer);
	void Draw(const VkCommandBuffer& buffer);

	VIDECL void CreateVertexBuffer(const List<sVertex>& vertices);
};

VISRCEND

#endif //VICTORIAM_VULKANVERTEXBUFFER_HPP
