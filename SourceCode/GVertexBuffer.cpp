//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "VulkanVertexBuffer.hpp"

VISRCBEG

pVertexBuffer cVertexBuffer::Create(pDevice& device, const List<sVertex>& vertices)
{
	return CreateSPtr<cVulkanVertexBuffer>(device, vertices);
}

VISRCEND
