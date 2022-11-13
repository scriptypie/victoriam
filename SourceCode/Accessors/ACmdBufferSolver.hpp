//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_ACMDBUFFERSOLVER_HPP
#define VICTORIAM_ACMDBUFFERSOLVER_HPP

#include "../VulkanBackend/VulkanCmdBufferSolver.hpp"

VISRCBEG

namespace Accessors
{
	class VIDECL CmdBufferSolver
	{
	public:
		VIDECL VIREQOUT inline static auto GetCmdBufferList(const PCmdBufferSolver& cmdBufferSolver)
		{
			return CCast<CVulkanCmdBufferSolver*>(cmdBufferSolver.get())->GetCmdBufferList();
		}
	};
}

VISRCEND

#endif //VICTORIAM_ACMDBUFFERSOLVER_HPP
