//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include <Victoriam/Graphics/GRenderSubPass.hpp>

#include "RendererSubPasses/DefaultRenderSubPass.hpp"

VISRCBEG

PRenderSubPass CRenderSubPass::CreateDefaultSubPass(PGraphicsContext &context, PSwapchain &swapchain, const PDescriptorSetLayout &setLayout)
{
	return CreateUPtr<CDefaultRenderSubPass>(context, swapchain, setLayout);
}

VISRCEND
