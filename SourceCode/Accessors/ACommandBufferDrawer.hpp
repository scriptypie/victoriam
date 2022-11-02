//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_ACOMMANDBUFFERDRAWER_HPP
#define VICTORIAM_ACOMMANDBUFFERDRAWER_HPP

#include"../VulkanCommandBufferDrawer.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL CommandBufferDrawer
	{
	public:
		VIDECL VIREQOUT inline static auto GetCommandBufferList(const PDrawCommandBuffer& drawCommandBuffer)
		{
			return CCast<CVulkanCommandBufferDrawer*>(drawCommandBuffer.get())->GetCommandBufferList();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ACOMMANDBUFFERDRAWER_HPP
