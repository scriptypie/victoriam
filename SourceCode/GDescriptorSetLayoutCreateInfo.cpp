//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#include <Victoriam/Graphics/Structs/GDescriptorSetLayoutCreateInfo.hpp>

VISRCBEG

SDescriptorSetLayoutCreateInfo& SDescriptorSetLayoutCreateInfo::AddBinding(const UInt32& binding,
                                                                           const Signal& type,
                                                                           const Signal& stage,
                                                                           const UInt32& count)
{
	ViAssert(Bindings.count(binding) == 0, "Binding already in use");

	SDescriptorSetBinding descriptorSetBinding = {};
	descriptorSetBinding.Binding = binding;
	descriptorSetBinding.ShaderStage = stage;
	descriptorSetBinding.DescriptorType = type;
	descriptorSetBinding.Count = count;

	Bindings[binding] = descriptorSetBinding;
	return *this;
}


VISRCEND
