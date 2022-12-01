//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include <Victoriam/Graphics/GRenderSubrender.hpp>

#include "RendererSubrenders/DefaultRenderSubrender.hpp"
#include "RendererSubrenders/PointLightSubrender.hpp"

VISRCBEG

PRenderSubrender
CRenderSubrender::CreateDefaultSubrender(PGraphicsContext &context, PRenderPass& renderPass, const PDescriptorSetLayout &setLayout)
{
	return FMakeUnique<CDefaultRenderSubrender>(context, renderPass, setLayout);
}

PRenderSubrender
CRenderSubrender::CreatePointLightSubrender(PGraphicsContext &context, PRenderPass& renderPass,
                                            const PDescriptorSetLayout &setLayout) {
	return FMakeUnique<CPointLightSubrender>(context, renderPass, setLayout);
}

VISRCEND
