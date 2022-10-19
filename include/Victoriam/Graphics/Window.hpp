//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_WINDOW_HPP
#define VICTORIAM_WINDOW_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/WindowCreateInfo.hpp>
#include <Victoriam/EventSystem/WindowEvents.hpp>

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
	virtual void SetEventCallbackFunction(const EventCallbackFn& fn) = 0;

	static SPtr<cWindow> Create(const sWindowCreateInfo& info);
};

VIDECL typedef SPtr<cWindow> pWindow;

VISRCEND

#endif //VICTORIAM_WINDOW_HPP
