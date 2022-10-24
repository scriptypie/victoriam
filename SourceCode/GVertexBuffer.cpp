//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "VulkanVertexBuffer.hpp"

VISRCBEG

PVertexBuffer CVertexBuffer::Create(PDevice& device, const List<SVertex>& vertices)
{
	return CreateSPtr<CVulkanVertexBuffer>(device, vertices);
}

VISRCEND
