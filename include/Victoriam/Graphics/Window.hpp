//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_WINDOW_HPP
#define VICTORIAM_WINDOW_HPP

#include <Victoriam/Core/Base.hpp>
#include <Victoriam/Graphics/WindowCreateInfo.hpp>
#include <Victoriam/EventSystem/WindowEvents.hpp>
#include <Victoriam/EventSystem/KeyboardEvents.hpp>

VISRCBEG

class cWindow
{
public:
	using EventCallbackFn = Function<void(cEvent&)>;

	virtual ~cWindow() = default;

	virtual void Update() = 0;
	virtual UInt32 GetWidth() const = 0;
	virtual UInt32 GetHeight() const = 0;
	virtual UInt32 GetOffsetX() const = 0;
	virtual UInt32 GetOffsetY() const = 0;
	virtual void SetEventCallbackFunction(const EventCallbackFn& fn) = 0;
	virtual void* GetNativeWindowVPtr() = 0;

	template<class T>
	inline T* GetNativeWindowPtr()
	{
		return static_cast<T*>(GetNativeWindowVPtr());
	}

	static SPtr<cWindow> Create(const sWindowCreateInfo& info);
};

VISRCEND

#endif //VICTORIAM_WINDOW_HPP
