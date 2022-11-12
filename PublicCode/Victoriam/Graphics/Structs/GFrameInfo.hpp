//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GFRAMEINFO_HPP
#define VICTORIAM_GFRAMEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GRendererConstants.hpp>

VISRCBEG

/**
 * Struct that handles all frame-related information.
 */
struct VIDECL SFrameInfo
{
	VIDECL SCommandBuffer CommandBuffer = {};
	VIDECL SDescriptorSet ConstantsDescriptorSet = {};
	VIDECL SRendererConstants Constants = {};
	VIDECL Float32 AspectRatio = {};
	VIDECL UInt32 ImageIndex = {};
	VIDECL UInt32 FrameIndex = {};

	VIDECL inline SFrameInfo() = default;
	VIDECL inline SFrameInfo(const SCommandBuffer& commandBuffer, const UInt32& imageIndex, const UInt32& frameIndex)
		: CommandBuffer(commandBuffer), ImageIndex(imageIndex), FrameIndex(frameIndex)
	{}
	VIDECL inline SFrameInfo(const SCommandBuffer& commandBuffer, const SDescriptorSet& descriptorSet, const UInt32& imageIndex, const UInt32& frameIndex, const Float32& aspectRatio)
		: CommandBuffer(commandBuffer), ConstantsDescriptorSet(descriptorSet), ImageIndex(imageIndex), FrameIndex(frameIndex), AspectRatio(aspectRatio)
	{}

	VIDECL inline explicit operator Bool() const { return CCast<Bool>(CommandBuffer); }
};

VISRCEND

#endif //VICTORIAM_GFRAMEINFO_HPP
