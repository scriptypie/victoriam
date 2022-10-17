//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_PIPELINE_HPP
#define VICTORIAM_PIPELINE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/PipelineCreateInfo.hpp>
#include <Victoriam/Graphics/Device.hpp>

VISRCBEG

class cPipeline
{
public:
	virtual ~cPipeline() = default;


	static SPtr<cPipeline> Create(const String& name, pDevice& device, const sPipelineCreateInfo& info);
};

VIDECL typedef SPtr<cPipeline> pPipeline;

VISRCEND

#endif //VICTORIAM_PIPELINE_HPP
