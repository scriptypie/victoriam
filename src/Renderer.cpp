//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include<Victoriam/Graphics/Renderer.hpp>

VISRCBEG

bool cRenderer::Setup(const sRendererCreateInfo &createInfo) {

	auto window = createInfo.WindowPtr;
	m_Device = cDevice::Create(window);
	m_Swapchain = cSwapchain::Create(m_Device, window->GetExtent());
	m_Pipeline = cPipeline::Create("Default", m_Device, m_Swapchain, sPipelineCreateInfo(window->GetWidth(), window->GetHeight()));

	return m_Device && m_Swapchain && m_Pipeline;
}

void cRenderer::DrawFrame() {
	BeginFrame();
	// additional tasks
	EndFrame();
}

void cRenderer::BeginFrame() {

}

void cRenderer::EndFrame() {

}

VISRCEND
