//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <Victoriam/Graphics/GCmdBufferSolver.hpp>

#include "VulkanCommandBufferDrawer.hpp"

VISRCBEG

PCmdBufferSolver CCmdBufferSolver::Create(PSwapchain &swapchain, PGraphicsContext& context)
{
	return CreateSPtr<CVulkanCmdBufferSolver>(swapchain, context);
}

VISRCEND
