//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_GWINDOW_HPP
#define VICTORIAM_GWINDOW_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include "Victoriam/Graphics/Structs/GWindowCreateInfo.hpp"
#include <Victoriam/EventSystem/EWindowEvents.hpp>

VISRCBEG

class CWindow
{
public:
	using EventCallbackFn = Function<void(CEvent&)>;

	virtual ~CWindow() = default;

	virtual void Update() = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetOffsetX() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetOffsetY() const = 0;
	VIDECL VIREQOUT virtual SWindowExtent GetExtent() const = 0;
	VIDECL virtual void SetExtent(const SWindowExtent& extent) = 0;
	virtual void SetEventCallbackFunction(const EventCallbackFn& fn) = 0;
	virtual void WaitForEvents() = 0;

	static SPtr<CWindow> Create(const SWindowCreateInfo& info);
};

VIDECL typedef SPtr<CWindow> PWindow;

VISRCEND

#endif //VICTORIAM_GWINDOW_HPP
