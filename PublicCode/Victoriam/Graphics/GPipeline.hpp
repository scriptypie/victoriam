//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GPIPELINE_HPP
#define VICTORIAM_GPIPELINE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include "Victoriam/Graphics/Structs/GPipelineCreateInfo.hpp"
#include <Victoriam/Graphics/GDevice.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>

VISRCBEG

class cPipeline
{
public:
	virtual ~cPipeline() = default;

	virtual void BindDrawCommandBuffer(const sCommandBuffer& buffer) = 0;

	static UPtr<cPipeline> Create(const String& name, pDevice& device, pSwapchain& swapchain, const sPipelineCreateInfo& info);
};

VIDECL typedef UPtr<cPipeline> pPipeline;

VISRCEND

#endif //VICTORIAM_GPIPELINE_HPP
