//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_GGRAPHICSCONTEXT_HPP
#define VICTORIAM_GGRAPHICSCONTEXT_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

using ImmediateGraphicsActionFN = std::function<void(SCommandBuffer)>;

class VIDECL CGraphicsContext
{
public:
	VIDECL virtual ~CGraphicsContext() = default;

	VIDECL virtual void WaitReleaseResources() = 0;
	VIDECL virtual void Execute(ImmediateGraphicsActionFN fn) = 0;

	VIDECL          virtual void CmdCreate(const UInt32& imageCount) = 0;
	VIDECL VIREQOUT virtual SCommandBuffer CmdBegin(const UInt32& imageIndex) const = 0;
	VIDECL          virtual void CmdEnd(const SCommandBuffer& cmdBuffer) const = 0;

	VIDECL VIREQOUT static PGraphicsContext Create(const CShared<CWindow>& window);
};

VISRCEND

#endif //VICTORIAM_GGRAPHICSCONTEXT_HPP
