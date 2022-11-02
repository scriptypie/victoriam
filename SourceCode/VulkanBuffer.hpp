//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_VULKANBUFFER_HPP
#define VICTORIAM_VULKANBUFFER_HPP

#include <Victoriam/Graphics/GBuffer.hpp>

#include "VulkanMemoryBuffer.hpp"

VISRCBEG

class VIDECL CVulkanBuffer : public CBuffer
{
	enum class ECType : UInt32 { None = 0U, VertexBuffer, IndexBuffer, UniformBuffer };
	ECType m_Type = ECType::None;
	PDevice& m_Device;
	PVulkanMemoryBuffer m_MemoryBuffer = nullptr;
	UInt64 m_Count = {};
public:
	VIDECL CVulkanBuffer(PDevice &device, const List<SVertex> &vertices);
	VIDECL CVulkanBuffer(PDevice &device, const List<UInt32> &indices);
	VIDECL CVulkanBuffer(PDevice &device, const UInt32& maxFramesInFlight);
	VIDECL ~CVulkanBuffer() = default;

	void Bind(const SCommandBuffer& buffer) override;
	void SubmitUniformBuffer(const SRendererConstants* constants, const UInt32& imageIndex) override;
	void Draw(const SCommandBuffer& buffer) const override;

private:
	VIDECL void CreateVertexBuffer(const List<SVertex>& vertices);
	VIDECL void CreateIndexBuffer(const List<UInt32>& indices);
	VIDECL void CreateUniformBuffer(const UInt32& maxFramesInFlight);
};

VISRCEND

#endif //VICTORIAM_VULKANBUFFER_HPP
