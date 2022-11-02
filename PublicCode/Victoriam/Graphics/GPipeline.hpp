//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GPIPELINE_HPP
#define VICTORIAM_GPIPELINE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include "Victoriam/Graphics/Structs/GPipelineCreateInfo.hpp"
#include "Victoriam/Graphics/Structs/GMaterialData.hpp"
#include <Victoriam/Graphics/GDevice.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>

VISRCBEG

class CPipeline
{
public:
	virtual ~CPipeline() = default;

	virtual void BindDrawCommandBuffer(const SCommandBuffer& buffer) = 0;
	virtual void PushMaterialData(const SCommandBuffer& buffer, const UInt32& offset, const SMaterialData* materialDatas) = 0;

	static UPtr<CPipeline> Create(const String& name, PDevice& device, PSwapchain& swapchain);
};

VIDECL typedef UPtr<CPipeline> PPipeline;

VISRCEND

#endif //VICTORIAM_GPIPELINE_HPP
