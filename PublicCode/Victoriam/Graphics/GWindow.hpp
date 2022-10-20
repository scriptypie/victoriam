//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_GWINDOW_HPP
#define VICTORIAM_GWINDOW_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include "Victoriam/Graphics/Structs/GWindowCreateInfo.hpp"
#include <Victoriam/EventSystem/EWindowEvents.hpp>

VISRCBEG

class cWindow
{
public:
	using EventCallbackFn = Function<void(cEvent&)>;

	virtual ~cWindow() = default;

	virtual void Update() = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetOffsetX() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetOffsetY() const = 0;
	VIDECL VIREQOUT virtual sWindowExtent GetExtent() const = 0;
	VIDECL virtual void SetExtent(const sWindowExtent& extent) = 0;
	virtual void SetEventCallbackFunction(const EventCallbackFn& fn) = 0;
	virtual void WaitForEvents() = 0;

	static SPtr<cWindow> Create(const sWindowCreateInfo& info);
};

VIDECL typedef SPtr<cWindow> pWindow;

VISRCEND

#endif //VICTORIAM_GWINDOW_HPP
