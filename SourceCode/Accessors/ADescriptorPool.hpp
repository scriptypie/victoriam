//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_ADESCRIPTORPOOL_HPP
#define VICTORIAM_ADESCRIPTORPOOL_HPP

#include "../VulkanBackend/VulkanDescriptorPool.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL DescriptorPool
	{
	public:
		VIDECL VIREQOUT static PGraphicsContext& GetContext(const PDescriptorPool& pool)
		{
			return CCast<CVulkanDescriptorPool*>(pool.get())->GetContext();
		}
		VIDECL VIREQOUT static VkDescriptorPool GetPool(const PDescriptorPool& pool)
		{
			return CCast<CVulkanDescriptorPool*>(pool.get())->GetPool();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ADESCRIPTORPOOL_HPP
