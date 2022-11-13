//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_AFRAMEBUFFER_HPP
#define VICTORIAM_AFRAMEBUFFER_HPP

#include "../VulkanFramebuffer.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL Framebuffer
	{
	public:
		VIDECL VIREQOUT inline static VkFramebuffer GetFramebuffer(const PFramebuffer& framebuffer)
		{
			return CCast<CVulkanFramebuffer*>(framebuffer.get())->GetFramebuffer();
		}
	};
}

VISRCEND

#endif //VICTORIAM_AFRAMEBUFFER_HPP
