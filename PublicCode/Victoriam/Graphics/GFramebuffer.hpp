//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_GFRAMEBUFFER_HPP
#define VICTORIAM_GFRAMEBUFFER_HPP

#include <Victoriam/Graphics/Structs/GFramebufferCreateInfo.hpp>

VISRCBEG

class VIDECL CFramebuffer {
public:
	VIDECL virtual ~CFramebuffer() = default;

	VIDECL VIREQOUT static PFramebuffer Create(PGraphicsContext& context, PRenderPass& renderPass, const SFramebufferCreateInfo& createInfo);
};

VISRCEND

#endif //VICTORIAM_GFRAMEBUFFER_HPP
