//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_VULKANVERTEXBUFFER_HPP
#define VICTORIAM_VULKANVERTEXBUFFER_HPP

#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "Accessors/ADevice.hpp"

VISRCBEG

namespace Accessors { class VertexBuffer; }

class VIDECL CVulkanVertexBuffer : public CVertexBuffer
{
	friend class Accessors::VertexBuffer;

	PDevice& m_Device;
	VkBuffer m_VertexBuffer = {};
	VkDeviceMemory m_VertexBufferMemory = {};
	UInt64 m_VertexCount = {};

public:
	CVulkanVertexBuffer(PDevice& device, const List<SVertex>& vertices);
	~CVulkanVertexBuffer() override;

	void Bind(const SCommandBuffer& buffer) override;
	void Draw(const SCommandBuffer& buffer) const override;
private:

	VIDECL void CreateVertexBuffer(const List<SVertex>& vertices);
};

VISRCEND

#endif //VICTORIAM_VULKANVERTEXBUFFER_HPP
