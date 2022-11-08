//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GPIPELINE_HPP
#define VICTORIAM_GPIPELINE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GPipelineCreateInfo.hpp>
#include <Victoriam/Graphics/Structs/GMaterialData.hpp>
#include <Victoriam/Graphics/Structs/GFrameInfo.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>

VISRCBEG

SignalDecl BindPointGraphics = 0;
SignalDecl BindPointCompute = 1;

class VIDECL CPipeline
{
public:
	VIDECL virtual ~CPipeline() = default;

	VIDECL virtual void BindCommandBuffer(const SCommandBuffer& buffer) const = 0;
	VIDECL virtual void PushMaterialData(const SCommandBuffer& buffer, const UInt32& offset, const SMaterialData* materialData) const = 0;
	VIDECL virtual void BindConstantsDescriptorSet(const Signal& bindPoint, const SFrameInfo& frameInfo) const = 0;

	VIDECL VIREQOUT static UPtr<CPipeline> Create(const String& name, PGraphicsContext& device, PSwapchain& swapchain, PDescriptorSetLayout& setLayout);
};

VIDECL typedef UPtr<CPipeline> PPipeline;

VISRCEND

#endif //VICTORIAM_GPIPELINE_HPP
