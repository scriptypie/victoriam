//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#ifndef VICTORIAM_VULKANINDEXBUFFER_HPP
#define VICTORIAM_VULKANINDEXBUFFER_HPP

#include <Victoriam/Graphics/GIndexBuffer.hpp>

#include "Accessors/ADevice.hpp"

VISRCBEG

namespace Accessors { class IndexBuffer; }

class CVulkanIndexBuffer : public CIndexBuffer
{
	friend class Accessors::IndexBuffer;

	PDevice& m_Device;
	VkBuffer m_IndexBuffer = {};
	VkDeviceMemory m_IndexBufferMemory = {};
	UInt64 m_IndexCount = {};
	Bool m_Recreated = false;
public:
	CVulkanIndexBuffer(PDevice& device, const List<UInt32>& indices);
	~CVulkanIndexBuffer() override;

	void Bind(const SCommandBuffer& buffer) override;
	void Draw(const SCommandBuffer& buffer) const override;
	inline void Recreated() override { m_Recreated = true; }
private:

	VIDECL void CreateIndexBuffer(const List<UInt32>& indices);

};

VISRCEND

#endif //VICTORIAM_VULKANINDEXBUFFER_HPP
