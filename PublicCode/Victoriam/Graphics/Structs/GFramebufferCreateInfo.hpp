//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_GFRAMEBUFFERCREATEINFO_HPP
#define VICTORIAM_GFRAMEBUFFERCREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

struct VIDECL SFramebufferCreateInfo {
	CSet<SImageViewObject> Attachments;
};

VISRCEND

#endif //VICTORIAM_GFRAMEBUFFERCREATEINFO_HPP
