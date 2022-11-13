//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_GRENDERPASSCREATEINFO_HPP
#define VICTORIAM_GRENDERPASSCREATEINFO_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/Graphics/Structs/GWindowExtent.hpp>

VISRCBEG

struct VIDECL SRenderPassCreateInfo {
	SVector2 Offset = {};
	SWindowExtent Extent = {};
	SVector4 ClearColor = {0.01F, 0.01F, 0.01F, 1.0F};
	Float32 Depth = {};
	UInt32 Stencil = {};
};

VISRCEND

#endif //VICTORIAM_GRENDERPASSCREATEINFO_HPP
