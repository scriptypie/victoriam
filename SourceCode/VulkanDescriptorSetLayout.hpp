//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_VULKANDESCRIPTORSETLAYOUT_HPP
#define VICTORIAM_VULKANDESCRIPTORSETLAYOUT_HPP

#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>

#include "Accessors/AGraphicsContext.hpp"

VISRCBEG

namespace Accessors { class DescriptorSetLayout; }

class VIDECL CVulkanDescriptorSetLayout : public CDescriptorSetLayout
{
	friend class Accessors::DescriptorSetLayout;
	PGraphicsContext& m_Context;
	VkDescriptorSetLayout m_Layout = {};
	DescriptorSetBindingList m_Bindings = {};
public:
	VIDECL CVulkanDescriptorSetLayout(PGraphicsContext &device, const SDescriptorSetLayoutCreateInfo &createInfo);
	VIDECL ~CVulkanDescriptorSetLayout() override;

	VIDECL VIREQOUT inline DescriptorSetBindingList& GetBindings() override { return m_Bindings; }
private:
	VIDECL VIREQOUT inline VkDescriptorSetLayout GetDescriptorSetLayout() const { return m_Layout; }

};

VISRCEND

#endif //VICTORIAM_VULKANDESCRIPTORSETLAYOUT_HPP
