//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_APIPELINE_HPP
#define VICTORIAM_APIPELINE_HPP

#include "../VulkanPipeline.hpp"

VISRCBEG

namespace Accessors
{

	class VIDECL Pipeline
	{
	public:
		VIDECL inline static void BindDrawCommandBuffer(const pPipeline& pipeline, const VkCommandBuffer&commandBuffer)
		{
			CCast<cVulkanPipeline*>(pipeline.get())->BindDrawCommandBuffer(commandBuffer);
		}
	};

}

VISRCEND

#endif //VICTORIAM_APIPELINE_HPP
