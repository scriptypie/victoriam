//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GSWAPCHAIN_HPP
#define VICTORIAM_GSWAPCHAIN_HPP

#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class VIDECL CSwapchain
{
public:
	VIDECL virtual ~CSwapchain() = default;

	VIDECL VIREQOUT virtual UInt32 AcquireNextImage(UInt32* imageIndex) = 0;
	VIDECL VIREQOUT virtual UInt32 GetImageCount() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetFrameIndex() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetMaxFramesInFlight() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual Float32 GetExtentAspectRatio() const = 0;
	VIDECL VIREQOUT virtual Bool CompareFormats(const UPtr<CSwapchain>& swapchain) const = 0;

	VIDECL VIREQOUT static UPtr<CSwapchain> Create(PGraphicsContext& context, const SWindowExtent& extent);
	VIDECL VIREQOUT static UPtr<CSwapchain> Create(PGraphicsContext& context, const SWindowExtent& extent, CSwapchain* prev);
};

VIDECL typedef UPtr<CSwapchain> PSwapchain;

VISRCEND

#endif //VICTORIAM_GSWAPCHAIN_HPP
