//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GSWAPCHAIN_HPP
#define VICTORIAM_GSWAPCHAIN_HPP

#include <Victoriam/Graphics/GDevice.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class CSwapchain
{
public:
	virtual ~CSwapchain() = default;

	VIDECL VIREQOUT virtual UInt32 AcquireNextImage(UInt32* imageIndex) = 0;
	VIDECL VIREQOUT virtual UInt32 GetImageCount() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetFrameIndex() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetMaxFramesInFlight() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual Float32 GetExtentAspectRatio() const = 0;
	VIDECL VIREQOUT virtual Bool CompareFormats(const UPtr<CSwapchain>& swapchain) const = 0;
	VIDECL virtual void BeginRenderPass(const SCommandBuffer& commandBuffer, UInt32 imageIndex) = 0;
	VIDECL virtual void EndRenderPass(const SCommandBuffer& commandBuffer) = 0;

	VIDECL static UPtr<CSwapchain> Create(PDevice& device, const SWindowExtent& extent);
	VIDECL static UPtr<CSwapchain> Create(PDevice& device, const SWindowExtent& extent, CSwapchain* prev);
};

VIDECL typedef UPtr<CSwapchain> PSwapchain;

VISRCEND

#endif //VICTORIAM_GSWAPCHAIN_HPP
