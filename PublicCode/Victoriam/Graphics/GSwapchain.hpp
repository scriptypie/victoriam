//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GSWAPCHAIN_HPP
#define VICTORIAM_GSWAPCHAIN_HPP

#include <Victoriam/Graphics/GDevice.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class cSwapchain
{
public:
	virtual ~cSwapchain() = default;

	VIDECL VIREQOUT virtual UInt32 AcquireNextImage(UInt32* imageIndex) = 0;
	VIDECL VIREQOUT virtual UInt32 GetImageCount() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual Float32 GetExtentAspectRatio() const = 0;

	VIDECL static UPtr<cSwapchain> Create(pDevice& device, const sWindowExtent& extent);
	VIDECL static UPtr<cSwapchain> Create(pDevice& device, const sWindowExtent& extent, cSwapchain* prev);
};

VIDECL typedef UPtr<cSwapchain> pSwapchain;

VISRCEND

#endif //VICTORIAM_GSWAPCHAIN_HPP
