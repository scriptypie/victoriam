//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GPIPELINECREATEINFO_HPP
#define VICTORIAM_GPIPELINECREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>

VISRCBEG

/**
 * Struct that contain all information required to create new pipeline object.
 */
struct VIDECL SPipelineCreateInfo
{
	UInt32 Width = {};
	UInt32 Height = {};
	String Name = {};
	Bool bProvideBindings = true;
	Bool bProvideAttributes = true;
	Bool bCreateConstantRanges = true;
};

VISRCEND

#endif //VICTORIAM_GPIPELINECREATEINFO_HPP
