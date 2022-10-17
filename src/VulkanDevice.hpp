//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANDEVICE_HPP
#define VICTORIAM_VULKANDEVICE_HPP

#include <Victoriam/Graphics/Device.hpp>

#include "Accessors/AWindow.hpp"
#include "GLFWWindow.hpp"

VISRCBEG

struct VIDECL sSwapchainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	List<VkSurfaceFormatKHR> formats;
	List<VkPresentModeKHR> presentModes;
};

struct VIDECL sQueueFamilyIndices
{
	UInt32 GraphicsFamily = {};
	UInt32 PresentFamily = {};
	Bool GraphicsFamilyHasValue = false;
	Bool PresentFamilyHasValue = false;
	VIDECL [[nodiscard]] inline Bool IsCompleted() const { return GraphicsFamilyHasValue && PresentFamilyHasValue; }
};

namespace Accessors { class Device; }

class cVulkanDevice : public cDevice
{
	friend class Accessors::Device;
#ifdef NDEBUG
		const Bool m_EnableValidation = false;
#else
		const Bool m_EnableValidation = true;
#endif
	SPtr<cWindow> m_Window;
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
	explicit cVulkanDevice(const SPtr<cWindow> &window);
	~cVulkanDevice() override;

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
	VIDECL sQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	VIDECL static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& info);
	VIDECL void HasGLFWRequiredInstanceExtensions();
	VIDECL Bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	VIDECL sSwapchainSupportDetails QuerySwapchainSupport(VkPhysicalDevice device);
private:
	VIDECL VIREQOUT inline VkCommandPool GetCommandPool() { return m_CmdPool; }
	VIDECL VIREQOUT inline VkDevice GetDevice() { return m_Device; }
	VIDECL VIREQOUT inline VkSurfaceKHR GetSurface() { return m_Surface; }
	VIDECL VIREQOUT inline sSwapchainSupportDetails GetSwapchainSupport() { return QuerySwapchainSupport(m_PhysicalDevice); }
	VIDECL VIREQOUT inline VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
	VIDECL VIREQOUT inline VkQueue GetPresentQueue() { return m_PresentQueue; }
};

VISRCEND

#endif //VICTORIAM_VULKANDEVICE_HPP
