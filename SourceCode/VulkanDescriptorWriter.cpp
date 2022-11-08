//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#include "VulkanDescriptorWriter.hpp"

VISRCBEG

CVulkanDescriptorWriter::CVulkanDescriptorWriter(PDescriptorPool &pool, PDescriptorSetLayout &layout) : m_Pool(pool), m_Layout(layout)
{}

Bool CVulkanDescriptorWriter::Build(SDescriptorSet &descriptorSet) {
	if (!m_Pool->AllocateDescriptorSet(m_Layout, descriptorSet))
		return false;
	Overwrite(descriptorSet);
	return true;
}

void CVulkanDescriptorWriter::Overwrite(SDescriptorSet &descriptorSet) {
	for (auto& write : m_WriteList)
		write.dstSet = CCast<VkDescriptorSet>(descriptorSet);
	auto& context = Accessors::DescriptorPool::GetContext(m_Pool);
	vkUpdateDescriptorSets(Accessors::GraphicsContext::GetDevice(context),
						   CCast<UInt32>(m_WriteList.size()), m_WriteList.data(), 0, nullptr);
}

void CVulkanDescriptorWriter::WriteBuffer(const UInt32 &binding, VkDescriptorBufferInfo *bufferInfo) {
	ViAssert(m_Layout->GetBindings().count(binding) == 1, "Layout does not contain specified binding!");

	auto& bindingDesc = m_Layout->GetBindings()[binding];
	ViAssert(
			bindingDesc.Count == 1,
			"Binding single descriptor info, but binding expects multiple");

	VkWriteDescriptorSet writeDescriptorSet = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };
	writeDescriptorSet.descriptorType = CCast<VkDescriptorType>(bindingDesc.DescriptorType);
	writeDescriptorSet.dstBinding = binding;
	writeDescriptorSet.pBufferInfo = bufferInfo;
	writeDescriptorSet.descriptorCount = bindingDesc.Count;

	m_WriteList.push_back(writeDescriptorSet);
}

void CVulkanDescriptorWriter::WriteImage(const UInt32 &binding, VkDescriptorImageInfo *imageInfo) {
	ViAssert(m_Layout->GetBindings().count(binding) == 1, "Layout does not contain specified binding!");

	auto& bindingDesc = m_Layout->GetBindings().at(binding);
	ViAssert(
			bindingDesc.Count == 1,
			"Binding single descriptor info, but binding expects multiple");

	VkWriteDescriptorSet writeDescriptorSet = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };
	writeDescriptorSet.descriptorType = CCast<VkDescriptorType>(bindingDesc.DescriptorType);
	writeDescriptorSet.dstBinding = binding;
	writeDescriptorSet.pImageInfo = imageInfo;
	writeDescriptorSet.descriptorCount = bindingDesc.Count;

	m_WriteList.push_back(writeDescriptorSet);
}

VISRCEND
