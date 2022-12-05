//
// Created by Вячеслав Кривенко on 30.11.2022.
//

#include "VulkanPicture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

VISRCBEG

CVulkanPicture::~CVulkanPicture() = default;

CVulkanPicture::CVulkanPicture(PGraphicsContext& context, const StringView &filename) {
	m_Metrics.HDR = stbi_is_hdr(filename.data());
	stbi_info(filename.data(),
	          &m_Metrics.Width,
	          &m_Metrics.Height,
	          &m_Metrics.Channels);
	UInt64 size = m_Metrics.Width * m_Metrics.Height * m_Metrics.Channels;

	m_Buffer = CVulkanMemoryBuffer::Create(context, size, 1, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	m_Buffer->Map();

	if (!m_Metrics.HDR) {
		stbi_uc *data = stbi_load(filename.data(),
		                          &m_Metrics.Width,
		                          &m_Metrics.Height,
		                          &m_Metrics.Channels, 3);
		m_Buffer->WriteToBuffer(data);
		stbi_image_free(data);
	} else {
		Float32 *data = stbi_loadf(filename.data(),
		                           &m_Metrics.Width,
		                           &m_Metrics.Height,
		                           &m_Metrics.Channels, 3);
		m_Buffer->WriteToBuffer(data);
		stbi_image_free(data);
	}

}

CVulkanPicture::CVulkanPicture(PGraphicsContext& context, const void *data, const UInt64 &size) {
	m_Metrics.HDR = stbi_is_hdr_from_memory(CCast<const stbi_uc*>(data), CCast<Int32>(size));
	stbi_info_from_memory(CCast<const stbi_uc*>(data), CCast<Int32>(size),
	          &m_Metrics.Width,
	          &m_Metrics.Height,
	          &m_Metrics.Channels);
	UInt64 picSize = m_Metrics.Width * m_Metrics.Height * m_Metrics.Channels;

	m_Buffer = CVulkanMemoryBuffer::Create(context, picSize, 1, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	m_Buffer->Map();

	if (!m_Metrics.HDR) {
		stbi_uc *idata = stbi_load_from_memory(CCast<const stbi_uc*>(data), CCast<Int32>(size),
		                          &m_Metrics.Width,
		                          &m_Metrics.Height,
		                          &m_Metrics.Channels, 3);
		m_Buffer->WriteToBuffer(idata);
		stbi_image_free(idata);
	} else {
		Float32 *idata = stbi_loadf_from_memory(CCast<const stbi_uc*>(data), CCast<Int32>(size),
		                           &m_Metrics.Width,
		                           &m_Metrics.Height,
		                           &m_Metrics.Channels, 3);
		m_Buffer->WriteToBuffer(idata);
		stbi_image_free(idata);
	}
}

SPictureMetrics CVulkanPicture::GetMetrics() const {
	return m_Metrics;
}

void *CVulkanPicture::GetMemory() const {
	return m_Buffer->GetMappedMemory();
}

void *CVulkanPicture::GetBuffer() const {
	return m_Buffer->GetBuffer();
}

UInt32 CVulkanPicture::GetWidth() const {
	return m_Metrics.Width;
}

UInt32 CVulkanPicture::GetHeight() const {
	return m_Metrics.Height;
}

UInt32 CVulkanPicture::GetChannels() const {
	return m_Metrics.Channels;
}

Bool CVulkanPicture::IsHDR() const {
	return m_Metrics.HDR;
}

VISRCEND
