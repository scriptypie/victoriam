//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_DEVICE_HPP
#define VICTORIAM_DEVICE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Window.hpp>

VISRCBEG

class cDevice
{
public:
	virtual ~cDevice() = default;

	VIDECL static SPtr<cDevice> Create(const SPtr<cWindow>& window);
};

VIDECL typedef SPtr<cDevice> pDevice;

VISRCEND

#endif //VICTORIAM_DEVICE_HPP
