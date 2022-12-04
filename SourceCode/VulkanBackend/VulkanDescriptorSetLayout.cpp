//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#include "VulkanDescriptorSetLayout.hpp"

VISRCBEG

namespace {

	inline VkDescriptorSetLayoutBinding Convert(const SDescriptorSetBinding &binding) {
		VkDescriptorSetLayoutBinding vkBinding = {};
		vkBinding.binding = binding.Binding;
		vkBinding.descriptorType = CCast<VkDescriptorType>(binding.DescriptorType);
		vkBinding.descriptorCount = 1;
		vkBinding.stageFlags = CCast<VkShaderStageFlags>(binding.ShaderStage);
		return vkBinding;
	}

}

CVulkanDescriptorSetLayout::CVulkanDescriptorSetLayout(PGraphicsContext &context, const SDescriptorSetLayoutCreateInfo &createInfo) : m_Context(context), m_Bindings(createInfo.Bindings)
{
	CSet<VkDescriptorSetLayoutBinding> bindings = {};

	for (auto [_, binding] : m_Bindings)
		bindings.PushBack(Convert(binding));

	VkDescriptorSetLayoutCreateInfo layoutCreateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
	layoutCreateInfo.bindingCount = CCast<UInt32>(bindings.Size());
	layoutCreateInfo.pBindings = bindings.Data();

	if (vkCreateDescriptorSetLayout(Accessors::GraphicsContext::GetDevice(m_Context), &layoutCreateInfo, nullptr, &m_Layout) != VK_SUCCESS)
		ViAbort("Failed to create descriptor set layout!");
}

CVulkanDescriptorSetLayout::~CVulkanDescriptorSetLayout()
{
	vkDestroyDescriptorSetLayout(Accessors::GraphicsContext::GetDevice(m_Context), m_Layout, nullptr);
	m_Layout = nullptr;
}

VISRCEND
