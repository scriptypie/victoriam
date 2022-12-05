//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_GIMAGEVIEW_HPP
#define VICTORIAM_GIMAGEVIEW_HPP

#include <Victoriam/Graphics/Structs/GImageViewCreateInfo.hpp>

VISRCBEG

class VIDECL CImageView {
public:
	VIDECL virtual ~CImageView() = default;
	VIDECL VIREQOUT virtual SImageViewObject GetObject() = 0;

	VIDECL VIREQOUT static PImageView Create(PGraphicsContext& context, const PImage& image, const SImageViewCreateInfo& createInfo);
};

VISRCEND

#endif //VICTORIAM_GIMAGEVIEW_HPP
