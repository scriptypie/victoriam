//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GDEVICE_HPP
#define VICTORIAM_GDEVICE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class cDevice
{
public:
	virtual ~cDevice() = default;

	VIDECL static SPtr<cDevice> Create(const SPtr<cWindow>& window);
};

VIDECL typedef SPtr<cDevice> pDevice;

VISRCEND

#endif //VICTORIAM_GDEVICE_HPP
