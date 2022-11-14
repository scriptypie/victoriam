//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANCMDBUFFERSOLVER_HPP
#define VICTORIAM_VULKANCMDBUFFERSOLVER_HPP

#include "Victoriam/Graphics/GCmdBufferSolver.hpp"

#include"../Accessors/ASwapchain.hpp"
#include"../Accessors/AGraphicsContext.hpp"

VISRCBEG

namespace Accessors { class CmdBufferSolver; }

class VIDECL CVulkanCmdBufferSolver : public CCmdBufferSolver {
	friend class Accessors::CmdBufferSolver;

	CList<VkCommandBuffer> m_CmdBuffers = {};
	PSwapchain& m_Swapchain;
	PGraphicsContext& m_Context;
public:
	VIDECL CVulkanCmdBufferSolver(PSwapchain& swapchain, PGraphicsContext& device);
	VIDECL ~CVulkanCmdBufferSolver() override;

	VIDECL VIREQOUT SCommandBuffer Begin(const PWorld& world, const UInt32& imageIndex) override;
	VIDECL          void End(const SCommandBuffer& commandBuffer) const override;

private:
	VIDECL void CreateCmdBuffers();
private:
	VIDECL VIREQOUT inline CList<VkCommandBuffer> GetCmdBufferList() const { return m_CmdBuffers; }
};

VISRCEND

#endif //VICTORIAM_VULKANCMDBUFFERSOLVER_HPP
