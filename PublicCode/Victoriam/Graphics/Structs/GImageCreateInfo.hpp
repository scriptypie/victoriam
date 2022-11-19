//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_GIMAGECREATEINFO_HPP
#define VICTORIAM_GIMAGECREATEINFO_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

SignalDecl ImageType1D = 0;
SignalDecl ImageType2D = 1;
SignalDecl ImageType3D = 2;

SignalDecl ImageViewType1D = 1;
SignalDecl ImageViewType2D = 2;
SignalDecl ImageViewType3D = 3;
SignalDecl ImageViewTypeCube = 4;

SignalDecl ImageFormatR8Unorm           = 9;
SignalDecl ImageFormatR8Snorm           = 10;
SignalDecl ImageFormatR8Uint            = 13;
SignalDecl ImageFormatR8SRGB            = 15;
SignalDecl ImageFormatR8G8Unorm         = 16;
SignalDecl ImageFormatR8G8Snorm         = 17;
SignalDecl ImageFormatR8G8Uint          = 20;
SignalDecl ImageFormatR8G8SRGB          = 22;
SignalDecl ImageFormatR8G8B8Unorm       = 23;
SignalDecl ImageFormatR8G8B8Snorm       = 24;
SignalDecl ImageFormatR8G8B8Uint        = 27;
SignalDecl ImageFormatR8G8B8SRGB        = 29;
SignalDecl ImageFormatR8G8B8A8Unorm     = 37;
SignalDecl ImageFormatR8G8B8A8Snorm     = 38;
SignalDecl ImageFormatR8G8B8A8Uint      = 41;
SignalDecl ImageFormatR8G8B8A8SRGB      = 43;
SignalDecl ImageFormatR16Unorm          = 70;
SignalDecl ImageFormatR16Snorm          = 71;
SignalDecl ImageFormatR16Uint           = 74;
SignalDecl ImageFormatR16G16Unorm       = 77;
SignalDecl ImageFormatR16G16Snorm       = 78;
SignalDecl ImageFormatR16G16Uint        = 81;
SignalDecl ImageFormatR16G16B16Unorm    = 84;
SignalDecl ImageFormatR16G16B16Snorm    = 85;
SignalDecl ImageFormatR16G16B16Uint     = 88;
SignalDecl ImageFormatR16G16B16A16Unorm = 91;
SignalDecl ImageFormatR16G16B16A16Snorm = 92;
SignalDecl ImageFormatR16G16B16A16Uint  = 95;

SignalDecl ImageUsageTransferSource         = 1;
SignalDecl ImageUsageTransferDest           = 2;
SignalDecl ImageUsageSampled                = 4;
SignalDecl ImageUsageStorage                = 8;
SignalDecl ImageUsageColorAttachment        = 16;
SignalDecl ImageUsageDepthStencilAttachment = 32;
SignalDecl ImageUsageInputAttachment        = 128;

SignalDecl ImageAspectColor   = 1;
SignalDecl ImageAspectDepth   = 2;
SignalDecl ImageAspectStencil = 4;
SignalDecl ImageAspectMeta    = 8;

SignalDecl ImageMemoryGPUOnly    = 1;
SignalDecl ImageMemoryVisible    = 2;
SignalDecl ImageMemoryCoherent   = 4;

struct VIDECL SImageCreateInfo {
	Signal Type;
	Signal ViewType;
	SExtent3D Extent;
	Signal Format;
	Signal Usage;
	Bool bCreateView;
	Signal Aspect;
	Signal MemoryType;
};

VISRCEND

#endif //VICTORIAM_GIMAGECREATEINFO_HPP
