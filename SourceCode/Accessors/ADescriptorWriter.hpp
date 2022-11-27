//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_ADESCRIPTORWRITER_HPP
#define VICTORIAM_ADESCRIPTORWRITER_HPP

#include "../VulkanBackend/VulkanDescriptorWriter.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL DescriptorWriter {
	public:
		VIDECL inline static void WriteBuffer(PDescriptorWriter& writer, const UInt32& binding, VkDescriptorBufferInfo* bufferInfo) {
			CCast<CVulkanDescriptorWriter*>(writer.get())->WriteBuffer(binding, bufferInfo);
		}
		VIDECL inline static void WriteImage(PDescriptorWriter& writer, const UInt32& binding, VkDescriptorImageInfo* imageInfo) {
			CCast<CVulkanDescriptorWriter*>(writer.get())->WriteImage(binding, imageInfo);
		}
	};
}

VISRCEND

#endif //VICTORIAM_ADESCRIPTORWRITER_HPP
