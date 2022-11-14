//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_GFRAMEBUFFER_HPP
#define VICTORIAM_GFRAMEBUFFER_HPP

#include <Victoriam/Graphics/Structs/GFramebufferCreateInfo.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>

VISRCBEG

class CRenderPass;
VIDECL typedef UPtr<CRenderPass> PRenderPass;

class VIDECL CFramebuffer {
public:
	VIDECL virtual ~CFramebuffer() = default;

	VIDECL VIREQOUT static SPtr<CFramebuffer> Create(PGraphicsContext& context, PRenderPass& renderPass, const SFramebufferCreateInfo& createInfo);
};

VIDECL typedef SPtr<CFramebuffer> PFramebuffer;

VISRCEND

#endif //VICTORIAM_GFRAMEBUFFER_HPP