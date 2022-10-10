//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_WINDOW_HPP
#define VICTORIAM_WINDOW_HPP

#include <Victoriam/Core/Base.hpp>
#include <Victoriam/Graphics/WindowCreateInfo.hpp>

VISRCBEG

class cWindow
{
public:
	using EventCallbackFn = Function<void(Event&)>;

	virtual ~cWindow() = default;

	virtual void Update() = 0;
	virtual UInt32 GetWidth() const = 0;
	virtual UInt32 GetHeight() const = 0;
	virtual UInt32 GetOffsetX() const = 0;
	virtual UInt32 GetOffsetY() const = 0;

	static SPtr<cWindow> Create(const sWindowCreateInfo& info);
};

VIDECL SPtr<cWindow> pWindow;

VISRCEND

#endif //VICTORIAM_WINDOW_HPP
