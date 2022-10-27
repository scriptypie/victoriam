//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#include <Victoriam/Graphics/GIndexBuffer.hpp>

#include "VulkanIndexBuffer.hpp"

VISRCBEG

PIndexBuffer CIndexBuffer::Create(PDevice& device, const List<UInt32> &indices)
{
	return CreateSPtr<CVulkanIndexBuffer>(device, indices);
}

VISRCEND
