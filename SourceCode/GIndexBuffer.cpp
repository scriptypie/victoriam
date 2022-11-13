//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include <Victoriam/Graphics/GIndexBuffer.hpp>

#include "VulkanBackend/VulkanIndexBuffer.hpp"

VISRCBEG

PIndexBuffer CIndexBuffer::Create(PGraphicsContext &context, const CList<UInt32> &indices) {
	return CreateSPtr<CVulkanIndexBuffer>(context, indices);
}

VISRCEND
