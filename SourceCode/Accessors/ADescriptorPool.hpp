//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_ADESCRIPTORPOOL_HPP
#define VICTORIAM_ADESCRIPTORPOOL_HPP

#include "../VulkanBackend/VulkanDescriptorPool.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL DescriptorPool {
	public:
		VIDECL VIREQOUT static PGraphicsContext& GetContext(const PDescriptorPool& pool) {
			return CCast<CVulkanDescriptorPool*>(pool.Get())->GetContext();
		}
		VIDECL VIREQOUT static VkDescriptorPool GetPool(const PDescriptorPool& pool) {
			return CCast<CVulkanDescriptorPool*>(pool.Get())->GetPool();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ADESCRIPTORPOOL_HPP
