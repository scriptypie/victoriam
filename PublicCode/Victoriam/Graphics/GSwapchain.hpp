//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GSWAPCHAIN_HPP
#define VICTORIAM_GSWAPCHAIN_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

class VIDECL CSwapchain
{
public:
	VIDECL virtual ~CSwapchain() = default;

	VIDECL VIREQOUT virtual UInt32 AcquireNextImage(UInt32* imageIndex) = 0;
	VIDECL VIREQOUT virtual UInt32 GetImageCount() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetFrameIndex() const = 0;
	VIDECL VIREQOUT virtual CSet<PFramebuffer>& GetFramebuffers() = 0;
	VIDECL virtual void CreateFramebuffers(PRenderPass& renderPass) = 0;
	VIDECL VIREQOUT virtual UInt32 GetMaxFramesInFlight() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual Float32 GetExtentAspectRatio() const = 0;
	VIDECL VIREQOUT virtual Bool CompareFormats(const CUnique<CSwapchain>& swapchain) const = 0;
	VIDECL virtual void CmdSubmit(const SCommandBuffer* buffers, const UInt32 *imageIndex) = 0;

	VIDECL VIREQOUT static PSwapchain Create(PGraphicsContext& context, const SExtent2D& extent);
	VIDECL VIREQOUT static PSwapchain Create(PGraphicsContext& context, const SExtent2D& extent, CSwapchain* prev);
};

VISRCEND

#endif //VICTORIAM_GSWAPCHAIN_HPP
