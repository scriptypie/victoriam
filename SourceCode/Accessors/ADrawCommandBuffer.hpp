//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_ADRAWCOMMANDBUFFER_HPP
#define VICTORIAM_ADRAWCOMMANDBUFFER_HPP

#include"../VulkanDrawCommandBuffer.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL DrawCommandBuffer
	{
	public:
		VIDECL VIREQOUT inline static auto GetCommandBufferList(const pDrawCommandBuffer& drawCommandBuffer)
		{
			return CCast<cVulkanDrawCommandBuffer*>(drawCommandBuffer.get())->GetCommandBufferList();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ADRAWCOMMANDBUFFER_HPP
