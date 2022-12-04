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
	CSet<VkDescriptorPoolSize> poolSizeList = {};

	for (auto poolSize : createInfo.PoolSizeList)
		poolSizeList.PushBack(Convert(poolSize));

	VkDescriptorPoolCreateInfo poolCreateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
	poolCreateInfo.poolSizeCount = CCast<UInt32>(poolSizeList.Size());
	poolCreateInfo.pPoolSizes = poolSizeList.Data();
	poolCreateInfo.maxSets = createInfo.MaxSets;
	poolCreateInfo.flags = createInfo.DescriptorPoolCreateSignal;

	if (vkCreateDescriptorPool(Accessors::GraphicsContext::GetDevice(m_Context), &poolCreateInfo, nullptr, &m_Pool) != VK_SUCCESS)
		ViAbort("Failed to create descriptor pool!");
}

CVulkanDescriptorPool::~CVulkanDescriptorPool()
{
	vkDestroyDescriptorPool(Accessors::GraphicsContext::GetDevice(m_Context), m_Pool, nullptr);
	m_Pool = nullptr;
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

void CVulkanDescriptorPool::FreeDescriptorSets(CSet<SDescriptorSet> &descriptors) const {
	vkFreeDescriptorSets(Accessors::GraphicsContext::GetDevice(m_Context), m_Pool,
	                     CCast<UInt32>(descriptors.Size()), CCast<VkDescriptorSet*>(descriptors.Data()));
}

void CVulkanDescriptorPool::ResetPool() {
	vkResetDescriptorPool(Accessors::GraphicsContext::GetDevice(m_Context), m_Pool, 0);
}

VISRCEND
