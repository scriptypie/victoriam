//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include <Victoriam/Graphics/GBuffer.hpp>

#include "VulkanBuffer.hpp"

VISRCBEG

PBuffer CBuffer::CreateVertexBuffer(PDevice &device, const List<SVertex> &vertices) {
	return CreateSPtr<CVulkanBuffer>(device, vertices);
}

PBuffer CBuffer::CreateIndexBuffer(PDevice &device, const List<UInt32> &indices) {
	return CreateSPtr<CVulkanBuffer>(device, indices);
}

PBuffer CBuffer::CreateUniformBuffer(PDevice& device, const PSwapchain& swaphain) {
	return CreateSPtr<CVulkanBuffer>(device, swaphain->GetMaxFramesInFlight());
}

VISRCEND
