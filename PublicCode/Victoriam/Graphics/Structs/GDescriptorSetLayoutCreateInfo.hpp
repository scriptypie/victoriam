//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORSETLAYOUTCREATEINFO_HPP
#define VICTORIAM_GDESCRIPTORSETLAYOUTCREATEINFO_HPP

#include <Victoriam/Graphics/GGraphicsContext.hpp>

VISRCBEG

SignalDecl DescriptorTypeSampler = 0;
SignalDecl DescriptorTypeSampledImage = 2;
SignalDecl DescriptorTypeStorageImage = 3;
SignalDecl DescriptorTypeUniformBuffer = 6;
SignalDecl DescriptorTypeUniformBufferDynamic = 8;

SignalDecl ShaderStageVertex = 1;
SignalDecl ShaderStageGeometry = 8;
SignalDecl ShaderStageFragment = 16;
SignalDecl ShaderStageAllStages = 0x7FFFFFFF;

/**
 * Binding is what we want to bind to descriptor set.
 */
struct VIDECL SDescriptorSetBinding
{
	UInt32 Binding = {};
	Signal DescriptorType = {};
	Signal ShaderStage = {};
	UInt32 Count = 1;
};

VIDECL typedef UnorderedMap<UInt32, SDescriptorSetBinding> DescriptorSetBindingList;

/**
 * Structure that handles all information required to create descriptor set object.
 */
struct VIDECL SDescriptorSetLayoutCreateInfo
{
	DescriptorSetBindingList Bindings = {};

	VIDECL SDescriptorSetLayoutCreateInfo& AddBinding(const UInt32& binding,
	                                                  const Signal& type,
	                                                  const Signal& stage,
	                                                  const UInt32& count = 1);
};

VISRCEND

#endif //VICTORIAM_GDESCRIPTORSETLAYOUTCREATEINFO_HPP
