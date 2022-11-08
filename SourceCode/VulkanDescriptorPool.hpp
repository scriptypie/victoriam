//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_VULKANDESCRIPTORPOOL_HPP
#define VICTORIAM_VULKANDESCRIPTORPOOL_HPP

#include <Victoriam/Graphics/GDescriptorPool.hpp>

#include "Accessors/AGraphicsContext.hpp"
#include "Accessors/ADescriptorSetLayout.hpp"

VISRCBEG

namespace Accessors { class DescriptorPool; }

class VIDECL CVulkanDescriptorPool : public CDescriptorPool
{
	friend class Accessors::DescriptorPool;
	PGraphicsContext& m_Context;
	VkDescriptorPool m_Pool = {};
public:
	VIDECL CVulkanDescriptorPool(PGraphicsContext& device, const SDescriptorPoolCreateInfo& createInfo);
	VIDECL ~CVulkanDescriptorPool() override;

	VIDECL Bool AllocateDescriptorSet(const PDescriptorSetLayout& layout, SDescriptorSet& descriptorSet) const override;
	VIDECL void FreeDescriptorSets(List<SDescriptorSet>& descriptors) const override;
	VIDECL void ResetPool() override;

private:
	VIDECL inline PGraphicsContext& GetContext() { return m_Context; }
	VIDECL inline VkDescriptorPool GetPool() { return m_Pool; }
};

VISRCEND

#endif //VICTORIAM_VULKANDESCRIPTORPOOL_HPP
