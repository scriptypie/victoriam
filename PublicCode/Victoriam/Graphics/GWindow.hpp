//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_GWINDOW_HPP
#define VICTORIAM_GWINDOW_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GWindowCreateInfo.hpp>
#include <Victoriam/EventSystem/EWindowEvents.hpp>

VISRCBEG

class VIDECL CWindow
{
public:
	using EventCallbackFn = CFunction<void(CEvent&)>;

	VIDECL virtual ~CWindow() = default;

	VIDECL          virtual void Update() = 0;
	VIDECL VIREQOUT virtual UInt32 GetWidth() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetHeight() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetOffsetX() const = 0;
	VIDECL VIREQOUT virtual UInt32 GetOffsetY() const = 0;
	VIDECL VIREQOUT virtual SExtent2D GetExtent() const = 0;
	VIDECL          virtual void SetExtent(const SExtent2D& extent) = 0;
	VIDECL          virtual void SetEventCallbackFunction(const EventCallbackFn& fn) = 0;
	VIDECL          virtual void WaitForEvents() = 0;

	VIDECL VIREQOUT static PWindow Create(const SWindowCreateInfo& info);
};

VISRCEND

#endif //VICTORIAM_GWINDOW_HPP
