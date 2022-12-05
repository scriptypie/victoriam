//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_GRENDERSUBRENDER_HPP
#define VICTORIAM_GRENDERSUBRENDER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GFrameInfo.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class VIDECL CRenderSubrender
{
public:
	VIDECL virtual ~CRenderSubrender() = default;

	VIDECL virtual void Compute(SFrameInfo& frameInfo, const PWorld& world) {}
	VIDECL virtual void Pass(SFrameInfo& frameInfo, const PWorld& world) {};

	VIDECL VIREQOUT static PRenderSubrender CreateDefaultSubrender(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout);
	VIDECL VIREQOUT static PRenderSubrender CreatePointLightSubrender(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout);
};

VISRCEND

#endif //VICTORIAM_GRENDERSUBRENDER_HPP
