//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORSETLAYOUTCREATEINFO_HPP
#define VICTORIAM_GDESCRIPTORSETLAYOUTCREATEINFO_HPP

#include <Victoriam/Graphics/GGraphicsContext.hpp>

VISRCBEG

Constant<Signal, 0> DescriptorTypeSampler;
Constant<Signal, 2> DescriptorTypeSampledImage;
Constant<Signal, 3> DescriptorTypeStorageImage;
Constant<Signal, 6> DescriptorTypeUniformBuffer;
Constant<Signal, 8> DescriptorTypeUniformBufferDynamic;

Constant<Signal, 1> ShaderStageVertex;
Constant<Signal, 8> ShaderStageGeometry;
Constant<Signal, 16> ShaderStageFragment;
Constant<Signal, 0x7FFFFFFF> ShaderStageAllStages;

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

VIDECL typedef CHashTable<UInt32, SDescriptorSetBinding> DescriptorSetBindingList;

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
