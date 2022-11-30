//
// Created by Вячеслав Кривенко on 30.11.2022.
//

#ifndef VICTORIAM_GPICTURE_HPP
#define VICTORIAM_GPICTURE_HPP

#include <Victoriam/Graphics/Structs/GPictureMetrics.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>

VISRCBEG

class VIDECL CPicture {
public:
	VIDECL virtual ~CPicture() = default;

	VIDECL VIREQOUT virtual SPictureMetrics GetMetrics() const = 0;
	VIDECL VIREQOUT virtual void*  GetMemory() const = 0;
	VIDECL VIREQOUT virtual void*  GetBuffer() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetChannels() const = 0;
	VIDECL VIREQOUT virtual Bool IsHDR() const = 0;

	VIDECL VIREQOUT static SShared<CPicture> Create(PGraphicsContext& context, const StringView& filename);
	VIDECL VIREQOUT static SShared<CPicture> Create(PGraphicsContext& context, const void* data, const UInt64& size);
};

VIDECL typedef SShared<CPicture> PPicture;

Bool operator==(const PPicture& a, const PPicture& b);
Bool operator!=(const PPicture& a, const PPicture& b);

VISRCEND

#endif //VICTORIAM_GPICTURE_HPP
