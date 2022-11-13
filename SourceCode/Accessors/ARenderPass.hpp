//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_ARENDERPASS_HPP
#define VICTORIAM_ARENDERPASS_HPP

#include "../VulkanRenderPass.hpp"

VISRCBEG

namespace Accessors
{
	class RenderPass
	{
	public:
		VIDECL VIREQOUT inline static VkRenderPass GetRenderPass(const PRenderPass& renderPass)
		{
			return CCast<CVulkanRenderPass*>(renderPass.get())->GetRenderPass();
		}
		VIDECL VIREQOUT inline static SExtent2D GetExtent(const PRenderPass& renderPass)
		{
			return CCast<CVulkanRenderPass*>(renderPass.get())->GetExtent();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ARENDERPASS_HPP
