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
		VIDECL VIREQOUT static VkRenderPass GetRenderPass(const PRenderPass& renderPass)
		{
			return CCast<CVulkanRenderPass*>(renderPass.get())->GetRenderPass();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ARENDERPASS_HPP
