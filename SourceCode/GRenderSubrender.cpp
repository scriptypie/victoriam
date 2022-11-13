//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include <Victoriam/Graphics/GRenderSubrender.hpp>

#include "RendererSubrenders/DefaultRenderSubrender.hpp"
#include "RendererSubrenders/PointLightSubrender.hpp"

VISRCBEG

PRenderSubrender
CRenderSubrender::CreateDefaultSubrender(PGraphicsContext &context, PSwapchain &swapchain, const PDescriptorSetLayout &setLayout)
{
	return CreateUPtr<CDefaultRenderSubrender>(context, swapchain, setLayout);
}

PRenderSubrender
CRenderSubrender::CreatePointLightSubrender(PGraphicsContext &context, PSwapchain &swapchain,
                                            const PDescriptorSetLayout &setLayout) {
	return CreateUPtr<CPointLightSubrender>(context, swapchain, setLayout);
}

VISRCEND
