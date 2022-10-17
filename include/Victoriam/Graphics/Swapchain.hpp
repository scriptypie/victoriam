//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_SWAPCHAIN_HPP
#define VICTORIAM_SWAPCHAIN_HPP

#include <Victoriam/Graphics/Device.hpp>
#include <Victoriam/Graphics/Window.hpp>

VISRCBEG

class cSwapchain
{
public:
	virtual ~cSwapchain() = default;

	VIDECL static UPtr<cSwapchain> Create(pDevice& device, const sWindowExtent& extent);
};

VIDECL typedef UPtr<cSwapchain> pSwapchain;

VISRCEND

#endif //VICTORIAM_SWAPCHAIN_HPP
