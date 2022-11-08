//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GRENDERERCREATEINFO_HPP
#define VICTORIAM_GRENDERERCREATEINFO_HPP

#include "Victoriam/Graphics/GGraphicsContext.hpp"
#include "Victoriam/Graphics/GSwapchain.hpp"
#include "Victoriam/Graphics/GWindow.hpp"
#include "Victoriam/Graphics/GPipeline.hpp"

VISRCBEG

struct VIDECL SRendererCreateInfo
{
	VIDECL PWindow WindowPtr = nullptr;
};

VISRCEND

#endif //VICTORIAM_GRENDERERCREATEINFO_HPP
