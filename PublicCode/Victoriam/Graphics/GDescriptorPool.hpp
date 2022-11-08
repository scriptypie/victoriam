//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORPOOL_HPP
#define VICTORIAM_GDESCRIPTORPOOL_HPP

#include <Victoriam/Graphics/Structs/GDescriptorPoolCreateInfo.hpp>
#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>

VISRCBEG

class VIDECL CDescriptorPool
{
public:
	VIDECL virtual ~CDescriptorPool() = default;

	VIDECL VIREQOUT virtual Bool AllocateDescriptorSet(const PDescriptorSetLayout& layout, SDescriptorSet& descriptorSet) const = 0;
	VIDECL virtual void FreeDescriptorSets(List<SDescriptorSet>& descriptors) const = 0;
	VIDECL virtual void ResetPool() = 0;

	VIDECL VIREQOUT static UPtr<CDescriptorPool> Create(PGraphicsContext& context, const SDescriptorPoolCreateInfo& createInfo);
};

VIDECL typedef UPtr<CDescriptorPool> PDescriptorPool;

VISRCEND

#endif //VICTORIAM_GDESCRIPTORPOOL_HPP
