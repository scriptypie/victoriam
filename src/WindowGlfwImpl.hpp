//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#ifndef VICTORIAM_WINDOWGLFWIMPL_HPP
#define VICTORIAM_WINDOWGLFWIMPL_HPP

#include <Victoriam/Graphics/Window.hpp>

VISRCBEG

class cWindowGLFWImpl : public cWindow {
	sWindowCreateInfo info;
public:
	~cWindowGLFWImpl() override = default;
	cWindowGLFWImpl(const sWindowCreateInfo& info);

	void Update() override;
	UInt32 GetWidth() const override;
	UInt32 GetHeight() const override;
	UInt32 GetOffsetX() const override;
	UInt32 GetOffsetY() const override;
};


VISRCEND

#endif //VICTORIAM_WINDOWGLFWIMPL_HPP
