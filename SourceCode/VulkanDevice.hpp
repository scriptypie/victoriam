//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANDEVICE_HPP
#define VICTORIAM_VULKANDEVICE_HPP

#include <Victoriam/Graphics/GDevice.hpp>

#include "Accessors/AWindow.hpp"
#include "GLFWWindow.hpp"

VISRCBEG

struct VIDECL SSwapchainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	List<VkSurfaceFormatKHR> formats;
	List<VkPresentModeKHR> presentModes;
};

struct VIDECL SQueueFamilyIndices
{
	UInt32 GraphicsFamily = {};
	UInt32 PresentFamily = {};
	Bool GraphicsFamilyHasValue = false;
	Bool PresentFamilyHasValue = false;
	VIDECL [[nodiscard]] inline Bool IsCompleted() const { return GraphicsFamilyHasValue && PresentFamilyHasValue; }
};

namespace Accessors { class Device; }

class CVulkanDevice : public CDevice
{
	friend class Accessors::Device;
	friend class CVulkanRenderer;
#ifdef NDEBUG
		const Bool m_EnableValidation = false;
#else
		const Bool m_EnableValidation = true;
#endif
	SPtr<CWindow> m_Window;
	VkInstance m_Instance{};
	VkDebugUtilsMessengerEXT m_DebugMessenger{};
	VkPhysicalDevice m_PhysicalDevice{};
	VkPhysicalDeviceProperties m_Properties{};
	VkCommandPool m_CmdPool{};
	VkDevice m_Device{};
	VkSurfaceKHR m_Surface{};
	VkQueue m_GraphicsQueue{};
	VkQueue m_PresentQueue{};
	const List<CString> VALIDATION_LAYERS =
	{ "VK_LAYER_KHRONOS_validation" };
	List<CString> DEVICE_EXTENSIONS =
	{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
public:
	explicit CVulkanDevice(const SPtr<CWindow> &window);
	~CVulkanDevice() override;

	void WaitReleaseResources() override;
private:
	void CreateGraphicsInstance();
	void SetupDebugMessenger();
	void CreateSurface();
	void ChoosePhysicalDevice();
	void CreateLogicalDevice();
	void CreateCommandPool();

	VIDECL Bool IsPhysicalDeviceSuitable(VkPhysicalDevice device);
	VIDECL VIREQOUT List<CString> GetRequiredExtensions() const;
	VIDECL Bool CheckValidationLayerSupport();
	VIDECL SQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	VIDECL VkFormat FindSupportedFormat(const List<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VIDECL static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& info);
	VIDECL void HasGLFWRequiredInstanceExtensions();
	VIDECL Bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	VIDECL SSwapchainSupportDetails QuerySwapchainSupport(VkPhysicalDevice device);

private:
	// API defined
	VIDECL void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
	VIDECL VkCommandBuffer BeginSingleTimeCommands();
	VIDECL void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
	VIDECL void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	VIDECL void CopyBufferToImage(VkBuffer buffer, VkImage image, UInt32 width, UInt32 height, UInt32 layerCount);
	VIDECL void CreateImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
	VIDECL UInt32 FindMemoryType(UInt32 typeFilter, VkMemoryPropertyFlags properties);
private:
	VIDECL VIREQOUT inline VkCommandPool GetCommandPool() { return m_CmdPool; }
	VIDECL VIREQOUT inline VkDevice GetDevice() { return m_Device; }
	VIDECL VIREQOUT inline VkSurfaceKHR GetSurface() { return m_Surface; }
	VIDECL VIREQOUT inline SSwapchainSupportDetails GetSwapchainSupport() { return QuerySwapchainSupport(m_PhysicalDevice); }
	VIDECL VIREQOUT inline VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
	VIDECL VIREQOUT inline VkQueue GetPresentQueue() { return m_PresentQueue; }
	VIDECL VIREQOUT inline VkInstance GetInstance() { return m_Instance; }
	VIDECL VIREQOUT inline VkPhysicalDevice GetPhysicalDevice() { return m_PhysicalDevice; }
};

VISRCEND

#endif //VICTORIAM_VULKANDEVICE_HPP
