//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANGRAPHICSCONTEXT_HPP
#define VICTORIAM_VULKANGRAPHICSCONTEXT_HPP

#include <Victoriam/Graphics/GGraphicsContext.hpp>

#include "../Accessors/AWindow.hpp"
#include "../GLFWWindow.hpp"

VISRCBEG

struct VIDECL SSwapchainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	CSet<VkSurfaceFormatKHR> formats;
	CSet<VkPresentModeKHR> presentModes;
};

struct VIDECL SQueueFamilyIndices
{
	UInt32 GraphicsFamily = {};
	UInt32 PresentFamily = {};
	Bool GraphicsFamilyHasValue = false;
	Bool PresentFamilyHasValue = false;
	VIDECL VIREQOUT inline Bool IsCompleted() const
	{
		return GraphicsFamilyHasValue && PresentFamilyHasValue;
	}
};

namespace Accessors { class GraphicsContext; }

class CVulkanGraphicsContext : public CGraphicsContext
{
	friend class Accessors::GraphicsContext;
	friend class CVulkanRenderer;
#ifdef NDEBUG
		const Bool m_EnableValidation = false;
#else
		const Bool m_EnableValidation = true;
#endif
	CShared<CWindow> m_Window = {};
	VkInstance m_Instance = {};
	VkDebugUtilsMessengerEXT m_DebugMessenger = {};
	VkPhysicalDevice m_PhysicalDevice = {};
	VkPhysicalDeviceProperties m_Properties = {};
	VkCommandPool m_CmdPool = {};
	CSet<VkCommandBuffer> m_CmdBuffers = {};
	VkDevice m_Device = {};
	VkSurfaceKHR m_Surface = {};
	VkQueue m_GraphicsQueue = {};
	VkQueue m_PresentQueue = {};
	const CSet<CString> VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation" };
	CSet<CString> DEVICE_EXTENSIONS = {VK_KHR_SWAPCHAIN_EXTENSION_NAME };
public:
	VIDECL explicit CVulkanGraphicsContext(const CShared<CWindow> &window);
	VIDECL ~CVulkanGraphicsContext() override;

	VIDECL void WaitReleaseResources() override;
	VIDECL void Execute(ImmediateGraphicsActionFN fn) override;

	VIDECL void CmdCreate(const UInt32& imageCount) override;
	VIDECL VIREQOUT SCommandBuffer CmdBegin(const UInt32& imageIndex) const override;
	VIDECL void CmdEnd(const SCommandBuffer& cmdBuffer) const override;
private:
	VIDECL void CreateGraphicsInstance();
	VIDECL void SetupDebugMessenger();
	VIDECL void CreateSurface();
	VIDECL void ChoosePhysicalDevice();
	VIDECL void CreateLogicalDevice();
	VIDECL void CreateCommandPool();

	VIDECL VIREQOUT Bool IsPhysicalDeviceSuitable(VkPhysicalDevice device);
	VIDECL VIREQOUT CSet<CString> GetRequiredExtensions() const;
	VIDECL VIREQOUT Bool CheckValidationLayerSupport();
	VIDECL VIREQOUT SQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	VIDECL VIREQOUT VkFormat FindSupportedFormat(const CSet<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VIDECL          static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& info);
	VIDECL          void HasGLFWRequiredInstanceExtensions();
	VIDECL VIREQOUT Bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	VIDECL VIREQOUT SSwapchainSupportDetails QuerySwapchainSupport(VkPhysicalDevice device);
private:
	VIDECL          void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
	VIDECL VIREQOUT VkCommandBuffer BeginSingleTimeCommands();
	VIDECL          void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
	VIDECL          void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	VIDECL          void CopyBufferToImage(VkBuffer buffer, VkImage image, UInt32 width, UInt32 height, UInt32 layerCount);
	VIDECL          void CreateImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkDeviceSize memoryOffset, VkImage &image, VkDeviceMemory &imageMemory);
	VIDECL VIREQOUT UInt32 FindMemoryType(UInt32 typeFilter, VkMemoryPropertyFlags properties);
private:
	VIDECL VIREQOUT inline VkCommandPool GetCommandPool() { return m_CmdPool; }
	VIDECL VIREQOUT inline VkDevice GetDevice() { return m_Device; }
	VIDECL VIREQOUT inline VkSurfaceKHR GetSurface() { return m_Surface; }
	VIDECL VIREQOUT inline SSwapchainSupportDetails GetSwapchainSupport() { return QuerySwapchainSupport(m_PhysicalDevice); }
	VIDECL VIREQOUT inline VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
	VIDECL VIREQOUT inline VkQueue GetPresentQueue() { return m_PresentQueue; }
	VIDECL VIREQOUT inline VkInstance GetInstance() { return m_Instance; }
	VIDECL VIREQOUT inline VkPhysicalDevice GetPhysicalDevice() { return m_PhysicalDevice; }
	VIDECL VIREQOUT inline VkPhysicalDeviceProperties GetPhysicalDeviceProperties() const { return m_Properties; }
};

VISRCEND

#endif //VICTORIAM_VULKANGRAPHICSCONTEXT_HPP
