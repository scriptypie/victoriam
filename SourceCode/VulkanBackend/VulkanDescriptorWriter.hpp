//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_VULKANDESCRIPTORWRITER_HPP
#define VICTORIAM_VULKANDESCRIPTORWRITER_HPP

#include "Victoriam/Graphics/GDescriptorWriter.hpp"

#include "../Accessors/ADescriptorSetLayout.hpp"
#include "../Accessors/ADescriptorPool.hpp"

VISRCBEG

namespace Accessors { class DescriptorWriter; }

class VIDECL CVulkanDescriptorWriter : public CDescriptorWriter
{
	friend class Accessors::DescriptorWriter;
	PDescriptorPool& m_Pool;
	PDescriptorSetLayout& m_Layout;
	CSet<VkWriteDescriptorSet> m_WriteList = {};
public:
	VIDECL CVulkanDescriptorWriter(PDescriptorPool &pool, PDescriptorSetLayout &layout);
	VIDECL ~CVulkanDescriptorWriter() override = default;

	VIDECL Bool Build(SDescriptorSet& descriptorSet) override;
	VIDECL void Overwrite(SDescriptorSet& descriptorSet) override;

private:
	VIDECL void WriteBuffer(const UInt32& binding, VkDescriptorBufferInfo* bufferInfo);
	VIDECL void WriteImage(const UInt32& binding, VkDescriptorImageInfo* imageInfo);

};

VISRCEND

#endif //VICTORIAM_VULKANDESCRIPTORWRITER_HPP
