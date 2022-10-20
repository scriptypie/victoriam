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

	virtual void RecreateSwapchain(const sWindowExtent& newExtent) = 0;

	VIDECL static UPtr<cSwapchain> Create(pDevice& device, const sWindowExtent& extent);
};

VIDECL typedef UPtr<cSwapchain> pSwapchain;

VISRCEND

#endif //VICTORIAM_GSWAPCHAIN_HPP
