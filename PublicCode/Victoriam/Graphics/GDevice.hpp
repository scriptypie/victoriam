//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GDEVICE_HPP
#define VICTORIAM_GDEVICE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class CDevice
{
public:
	virtual ~CDevice() = default;

	virtual void WaitReleaseResources() = 0;

	VIDECL static SPtr<CDevice> Create(const SPtr<CWindow>& window);
};

VIDECL typedef SPtr<CDevice> PDevice;

VISRCEND

#endif //VICTORIAM_GDEVICE_HPP
