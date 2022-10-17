//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_PIPELINE_HPP
#define VICTORIAM_PIPELINE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/PipelineCreateInfo.hpp>
#include <Victoriam/Graphics/Device.hpp>
#include <Victoriam/Graphics/Swapchain.hpp>

VISRCBEG

class cPipeline
{
public:
	virtual ~cPipeline() = default;

	static UPtr<cPipeline> Create(const String& name, pDevice& device, pSwapchain& swapchain, const sPipelineCreateInfo& info);
};

VIDECL typedef UPtr<cPipeline> pPipeline;

VISRCEND

#endif //VICTORIAM_PIPELINE_HPP
