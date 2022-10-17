//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_RENDERER_HPP
#define VICTORIAM_RENDERER_HPP

#include <Victoriam/Graphics/RendererCreateInfo.hpp>

VISRCBEG

class cRenderer
{
	pDevice m_Device = nullptr;
	pPipeline m_Pipeline = nullptr;
	pSwapchain m_Swapchain = nullptr;
public:
	inline cRenderer() = default;
	inline ~cRenderer() = default;

	bool Setup(const sRendererCreateInfo& createInfo);

	void DrawFrame();
private:
	void BeginFrame();
	void EndFrame();
};

VISRCEND

#endif //VICTORIAM_RENDERER_HPP
