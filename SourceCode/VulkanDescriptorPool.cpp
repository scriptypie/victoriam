//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#include "VulkanDescriptorPool.hpp"

VISRCBEG

namespace {

	inline VkDescriptorPoolSize Convert(const SDescriptorPoolSize &size) {
		return { CCast<VkDescriptorType>(size.DescriptorType), size.DescriptorCount };
	}

}

CVulkanDescriptorPool::CVulkanDescriptorPool(PGraphicsContext &context, const SDescriptorPoolCreateInfo &createInfo)
	: m_Context(context)
{
	List<VkDescriptorPoolSize> poolSizeList = {};

	for (auto poolSize : createInfo.PoolSizeList)
		poolSizeList.push_back(Convert(poolSize));

	VkDescriptorPoolCreateInfo poolCreateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
	poolCreateInfo.poolSizeCount = CCast<UInt32>(poolSizeList.size());
	poolCreateInfo.pPoolSizes = poolSizeList.data();
	poolCreateInfo.maxSets = createInfo.MaxSets;
	poolCreateInfo.flags = createInfo.DescriptorPoolCreateSignal;

	if (vkCreateDescriptorPool(Accessors::GraphicsContext::GetDevice(m_Context), &poolCreateInfo, nullptr, &m_Pool) != VK_SUCCESS)
		ViAbort("Failed to create descriptor pool!");
}

CVulkanDescriptorPool::~CVulkanDescriptorPool()
{
	vkDestroyDescriptorPool(Accessors::GraphicsContext::GetDevice(m_Context), m_Pool, nullptr);
}

Bool CVulkanDescriptorPool::AllocateDescriptorSet(const PDescriptorSetLayout &layout, SDescriptorSet &descriptorSet) const {
	VkDescriptorSetAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
	allocateInfo.descriptorPool = m_Pool;
	allocateInfo.descriptorSetCount = 1;
	auto descriptorSetLayout = Accessors::DescriptorSetLayout::GetDescriptorSetLayout(layout);
	allocateInfo.pSetLayouts = &descriptorSetLayout;

	if (vkAllocateDescriptorSets(Accessors::GraphicsContext::GetDevice(m_Context), &allocateInfo, CCast<VkDescriptorSet*>(&descriptorSet)) != VK_SUCCESS)
		return false;
	return true;
}

void CVulkanDescriptorPool::FreeDescriptorSets(List<SDescriptorSet> &descriptors) const {
	vkFreeDescriptorSets(Accessors::GraphicsContext::GetDevice(m_Context), m_Pool,
	                     CCast<UInt32>(descriptors.size()), CCast<VkDescriptorSet*>(descriptors.data()));
}

void CVulkanDescriptorPool::ResetPool() {
	vkResetDescriptorPool(Accessors::GraphicsContext::GetDevice(m_Context), m_Pool, 0);
}

VISRCEND
