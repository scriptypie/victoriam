//
// Created by Вячеслав Кривенко on 30.11.2022.
//

#ifndef VICTORIAM_GPICTUREMETRICS_HPP
#define VICTORIAM_GPICTUREMETRICS_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

struct VIDECL SPictureMetrics {
	Int32 Width;
	Int32 Height;
	Int32 Channels;
	Bool HDR;
};

struct VIDECL SPictureMemory {
	void* Data;
	UInt8 _unused : 1;
};

VISRCEND

#endif //VICTORIAM_GPICTUREMETRICS_HPP
