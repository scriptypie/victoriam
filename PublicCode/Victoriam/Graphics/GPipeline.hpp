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
#include <Victoriam/Graphics/GRenderPass.hpp>
#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>

VISRCBEG

Constant<Signal, 0x00000000> BindPointGraphics;
Constant<Signal, 0x00000001> BindPointCompute;

/**
 *
 */
class VIDECL CPipeline
{
public:
	VIDECL virtual ~CPipeline() = default;

	VIDECL virtual void BindCommandBuffer(const SCommandBuffer& buffer) const = 0;

	template<class T>
	VIDECL inline void PushSimpleData(const SCommandBuffer& buffer, const UInt32& offset, const T* data) {
		PushSimpleData(buffer, offset, data, sizeof(T));
	}

	VIDECL virtual void PushSimpleData(const SCommandBuffer& buffer, const UInt32& offset, const void* data, const UInt32& dataSize) const = 0;
	VIDECL virtual void BindConstantsDescriptorSet(const Signal& bindPoint, const SFrameInfo& frameInfo) const = 0;

	template<class T>
	VIDECL VIREQOUT inline static CUnique<CPipeline> CreateFor(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout, const SPipelineCreateInfo& createInfo) {
		return Create(context, renderPass, setLayout, createInfo, sizeof(T));
	}

	VIDECL VIREQOUT static CUnique<CPipeline> Create(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout, const SPipelineCreateInfo& createInfo, const UInt32& pushDataSize);
};

VIDECL typedef CUnique<CPipeline> PPipeline;

VISRCEND

#endif //VICTORIAM_GPIPELINE_HPP
