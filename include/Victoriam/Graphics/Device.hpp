//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_DEVICE_HPP
#define VICTORIAM_DEVICE_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Window.hpp>

VISRCBEG

enum class ecDeviceProperty : UInt32
{
	CommandPool,
	Device,
	Surface,
	GraphicsQueue,
	PresentQueue,
	SwapchainSupportDetails,
};

class cDevice
{
public:
	virtual ~cDevice() = default;

	VIDECL virtual void* GetProperty(const ecDeviceProperty& property) = 0;
	VIDECL static SPtr<cDevice> Create(const SPtr<cWindow>& window);
};

VIDECL typedef SPtr<cDevice> pDevice;

VISRCEND

#endif //VICTORIAM_DEVICE_HPP
