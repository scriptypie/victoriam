//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_GIMAGEVIEW_HPP
#define VICTORIAM_GIMAGEVIEW_HPP

#include <Victoriam/Graphics/Structs/GImageViewCreateInfo.hpp>

VISRCBEG

class CImage;
typedef CShared<CImage> PImage;

class CGraphicsContext;
typedef CShared<CGraphicsContext> PGraphicsContext;

class VIDECL CImageView {
public:
	VIDECL virtual ~CImageView() = default;
	VIDECL VIREQOUT virtual SImageViewObject GetObject() = 0;

	VIDECL VIREQOUT static CShared<CImageView> Create(PGraphicsContext& context, const PImage& image, const SImageViewCreateInfo& createInfo);
};

VIDECL typedef CShared<CImageView> PImageView;

VISRCEND

#endif //VICTORIAM_GIMAGEVIEW_HPP
