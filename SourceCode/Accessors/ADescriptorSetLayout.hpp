//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_ADESCRIPTORSETLAYOUT_HPP
#define VICTORIAM_ADESCRIPTORSETLAYOUT_HPP

#include "../VulkanBackend/VulkanDescriptorSetLayout.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL DescriptorSetLayout {
	public:
		VIDECL VIREQOUT static VkDescriptorSetLayout GetDescriptorSetLayout(const PDescriptorSetLayout& descriptorSetLayout) {
			return CCast<CVulkanDescriptorSetLayout*>(descriptorSetLayout.get())->GetDescriptorSetLayout();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ADESCRIPTORSETLAYOUT_HPP
