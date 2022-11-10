//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_GCMDBUFFERSOLVER_HPP
#define VICTORIAM_GCMDBUFFERSOLVER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GPipeline.hpp>
#include <Victoriam/Graphics/GBuffer.hpp>
#include <Victoriam/World/WWorld.hpp>
#include <Victoriam/Graphics/Structs/GFrameInfo.hpp>

VISRCBEG

/**
 * Manager-ish class that creates command buffer objects, and ends it.
 * Basically named as solver, but probably should be named an another way.
 */
class VIDECL CCmdBufferSolver
{
public:
	VIDECL virtual ~CCmdBufferSolver() = default;
	/**
	 * Setup and create command buffer, associated with frame.
	 * @return New allocated command buffer
	 */
	VIDECL VIREQOUT virtual SCommandBuffer Begin(const PWorld& world, const UInt32& imageIndex) = 0;
	/**
	 * Ends command buffer and submit it to GPU.
	 * @param commandBuffer Valid cmd buffer.
	 */
	VIDECL virtual void End(const SCommandBuffer& commandBuffer) const = 0;
	/**
	 * Creates pointer type of class cmd buffer solver.
	 * @param swapchain Valid current swapchain.
	 * @param context Current graphics context.
	 * @return Pointer type of class cmd buffer solver.
	 */
	VIDECL VIREQOUT static SPtr<CCmdBufferSolver> Create(PSwapchain& swapchain, PGraphicsContext& context);
};

/**
 * Command buffer solver - manager of command buffers in engine.
 */
VIDECL typedef SPtr<CCmdBufferSolver> PCmdBufferSolver;

VISRCEND

#endif //VICTORIAM_GCMDBUFFERSOLVER_HPP
