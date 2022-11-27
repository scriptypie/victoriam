//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_GIMAGE_HPP
#define VICTORIAM_GIMAGE_HPP

#include <Victoriam/Graphics/Structs/GImageCreateInfo.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GImageView.hpp>

VISRCBEG

class VIDECL CImage {
public:
	VIDECL virtual ~CImage() = default;

	VIDECL VIREQOUT virtual SExtent3D GetExtent() const = 0;
	VIDECL VIREQOUT virtual UInt32    GetWidth()  const = 0;
	VIDECL VIREQOUT virtual UInt32    GetHeight() const = 0;
	VIDECL VIREQOUT virtual Signal    GetType()   const = 0;

	VIDECL VIREQOUT static SShared<CImage> Create(PGraphicsContext& context, const SImageCreateInfo& createInfo);
};

VIDECL typedef SShared<CImage> PImage;

VISRCEND

#endif //VICTORIAM_GIMAGE_HPP
