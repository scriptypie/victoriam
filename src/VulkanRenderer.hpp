//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANRENDERER_HPP
#define VICTORIAM_VULKANRENDERER_HPP

#include <Victoriam/Graphics/Renderer.hpp>

#include "VulkanDevice.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanDrawCommandBuffer.hpp"

#include "Accessors/ADrawCommandBuffer.hpp"

VISRCBEG

class cVulkanRenderer : public cRenderer {
	VIDECL pDevice m_Device;
	VIDECL pSwapchain m_Swapchain;
	VIDECL pPipeline m_Pipeline;
	VIDECL pDrawCommandBuffer m_DrawCommandBuffer;
public:
	cVulkanRenderer(const sRendererCreateInfo& createInfo);
	~cVulkanRenderer() override;

	void DrawFrame() override;
	void Shutdown() override;
private:
	void BeginFrame();
	void EndFrame();
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
