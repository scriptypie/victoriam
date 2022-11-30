//
// Created by Вячеслав Кривенко on 30.11.2022.
//

#ifndef VICTORIAM_VULKANPICTURE_HPP
#define VICTORIAM_VULKANPICTURE_HPP

#include <Victoriam/Graphics/GPicture.hpp>
#include "VulkanMemoryBuffer.hpp"

VISRCBEG

class VIDECL CVulkanPicture : public CPicture {
	SPictureMetrics m_Metrics = {};
	PVulkanMemoryBuffer m_Buffer = {};
public:
	VIDECL ~CVulkanPicture() override;
	VIDECL CVulkanPicture(PGraphicsContext& context, const StringView& filename);
	VIDECL CVulkanPicture(PGraphicsContext& context, const void* data, const UInt64& size);

	VIDECL VIREQOUT SPictureMetrics GetMetrics() const override;
	VIDECL VIREQOUT void*  GetMemory() const override;
	VIDECL VIREQOUT void*  GetBuffer() const override;
	VIDECL VIREQOUT UInt32 GetWidth() const override;
	VIDECL VIREQOUT UInt32 GetHeight() const override;
	VIDECL VIREQOUT UInt32 GetChannels() const override;
	VIDECL VIREQOUT Bool IsHDR() const override;

private:

};

VISRCEND

#endif //VICTORIAM_VULKANPICTURE_HPP
