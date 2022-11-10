//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GFRAMEINFO_HPP
#define VICTORIAM_GFRAMEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

/**
 * Struct that handles all frame-related information.
 */
struct VIDECL SFrameInfo
{
	VIDECL SCommandBuffer CommandBuffer = {};
	VIDECL SDescriptorSet ConstantsDescriptorSet = {};
	VIDECL UInt32 ImageIndex = {};

	VIDECL inline SFrameInfo() = default;
	VIDECL inline SFrameInfo(const SCommandBuffer& commandBuffer, const UInt32& imageIndex)
		: CommandBuffer(commandBuffer), ImageIndex(imageIndex)
	{}
	VIDECL inline SFrameInfo(const SCommandBuffer& commandBuffer, const SDescriptorSet& descriptorSet, const UInt32& imageIndex)
		: CommandBuffer(commandBuffer), ConstantsDescriptorSet(descriptorSet), ImageIndex(imageIndex)
	{}

	VIDECL inline explicit operator Bool() const { return CCast<Bool>(CommandBuffer); }
};

VISRCEND

#endif //VICTORIAM_GFRAMEINFO_HPP
