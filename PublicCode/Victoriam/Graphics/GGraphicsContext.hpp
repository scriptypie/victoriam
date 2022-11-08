//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GGRAPHICSCONTEXT_HPP
#define VICTORIAM_GGRAPHICSCONTEXT_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class VIDECL CGraphicsContext
{
public:
	VIDECL virtual ~CGraphicsContext() = default;

	VIDECL virtual void WaitReleaseResources() = 0;

	VIDECL VIREQOUT static SPtr<CGraphicsContext> Create(const SPtr<CWindow>& window);
};

VIDECL typedef SPtr<CGraphicsContext> PGraphicsContext;

VISRCEND

#endif //VICTORIAM_GGRAPHICSCONTEXT_HPP
