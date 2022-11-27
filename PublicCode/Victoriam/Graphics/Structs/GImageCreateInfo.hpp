//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_GIMAGECREATEINFO_HPP
#define VICTORIAM_GIMAGECREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

Constant<Signal, 0>     ImageType1D;
Constant<Signal, 1>     ImageType2D;
Constant<Signal, 2>     ImageType3D;

Constant<Signal, 1>     ImageViewType1D;
Constant<Signal, 2>     ImageViewType2D;
Constant<Signal, 3>     ImageViewType3D;
Constant<Signal, 4>     ImageViewTypeCube;

Constant<Signal, 9>     ImageFormatR8Unorm;
Constant<Signal, 10>    ImageFormatR8Snorm;
Constant<Signal, 13>    ImageFormatR8Uint;
Constant<Signal, 15>    ImageFormatR8SRGB;
Constant<Signal, 16>    ImageFormatR8G8Unorm;
Constant<Signal, 17>    ImageFormatR8G8Snorm;
Constant<Signal, 20>    ImageFormatR8G8Uint;
Constant<Signal, 22>    ImageFormatR8G8SRGB;
Constant<Signal, 23>    ImageFormatR8G8B8Unorm;
Constant<Signal, 24>    ImageFormatR8G8B8Snorm;
Constant<Signal, 27>    ImageFormatR8G8B8Uint;
Constant<Signal, 29>    ImageFormatR8G8B8SRGB;
Constant<Signal, 37>    ImageFormatR8G8B8A8Unorm;
Constant<Signal, 38>    ImageFormatR8G8B8A8Snorm;
Constant<Signal, 41>    ImageFormatR8G8B8A8Uint;
Constant<Signal, 43>    ImageFormatR8G8B8A8SRGB;
Constant<Signal, 70>    ImageFormatR16Unorm;
Constant<Signal, 71>    ImageFormatR16Snorm;
Constant<Signal, 74>    ImageFormatR16Uint;
Constant<Signal, 77>    ImageFormatR16G16Unorm;
Constant<Signal, 78>    ImageFormatR16G16Snorm;
Constant<Signal, 81>    ImageFormatR16G16Uint;
Constant<Signal, 84>    ImageFormatR16G16B16Unorm;
Constant<Signal, 85>    ImageFormatR16G16B16Snorm;
Constant<Signal, 88>    ImageFormatR16G16B16Uint;
Constant<Signal, 91>    ImageFormatR16G16B16A16Unorm;
Constant<Signal, 92>    ImageFormatR16G16B16A16Snorm;
Constant<Signal, 95>    ImageFormatR16G16B16A16Uint;
Constant<Signal, 126>   ImageFormatD32Sfloat;
Constant<Signal, 130>   ImageFormatD32SfloatS8Uint;

Constant<Signal, 1>     ImageUsageTransferSource;
Constant<Signal, 2>     ImageUsageTransferDest;
Constant<Signal, 4>     ImageUsageSampled;
Constant<Signal, 8>     ImageUsageStorage;
Constant<Signal, 16>    ImageUsageColorAttachment;
Constant<Signal, 32>    ImageUsageDepthStencilAttachment;
Constant<Signal, 128>   ImageUsageInputAttachment;

Constant<Signal, 1>     ImageAspectColor;
Constant<Signal, 2>     ImageAspectDepth;
Constant<Signal, 4>     ImageAspectStencil;
Constant<Signal, 8>     ImageAspectMeta;

Constant<Signal, 1>     ImageMemoryGPUOnly;
Constant<Signal, 2>     ImageMemoryVisible;
Constant<Signal, 4>     ImageMemoryCoherent;

struct VIDECL SImageCreateInfo {
	Signal Type;
	SExtent3D Extent;
	Signal Format;
	Signal Usage;
	Bool bCreateView;
	Signal Aspect;
	Signal MemoryType;
	Signal ViewType;
};

VISRCEND

#endif //VICTORIAM_GIMAGECREATEINFO_HPP
