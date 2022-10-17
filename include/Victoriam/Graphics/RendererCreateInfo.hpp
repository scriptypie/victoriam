//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_RENDERERCREATEINFO_HPP
#define VICTORIAM_RENDERERCREATEINFO_HPP

#include <Victoriam/Graphics/Device.hpp>
#include <Victoriam/Graphics/Swapchain.hpp>
#include <Victoriam/Graphics/Window.hpp>
#include <Victoriam/Graphics/Pipeline.hpp>

VISRCBEG

struct VIDECL sRendererCreateInfo
{
	VIDECL pWindow WindowPtr = nullptr;
};

VISRCEND

#endif //VICTORIAM_RENDERERCREATEINFO_HPP
