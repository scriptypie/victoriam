//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GFRAMEINFO_HPP
#define VICTORIAM_GFRAMEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

struct VIDECL SFrameInfo
{
	VIDECL SCommandBuffer CommandBuffer = {};

	VIDECL inline explicit operator Bool() const { return CCast<Bool>(CommandBuffer); }
};

VISRCEND

#endif //VICTORIAM_GFRAMEINFO_HPP
