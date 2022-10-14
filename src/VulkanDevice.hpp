//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANDEVICE_HPP
#define VICTORIAM_VULKANDEVICE_HPP

#include <Victoriam/Graphics/Device.hpp>

#include "WindowAccessor.hpp"
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

class cVulkanDevice : public cDevice, public cWindowAccessor
{
	friend class cDeviceAccessor;
#ifdef NDEBUG
		const Bool m_EnableValidation = false;
#else
		const Bool m_EnableValidation = true;
#endif
	SPtr<cWindow> m_Window;
	VkInstance m_Instance{};
	VkDebugUtilsMessengerEXT m_DebugMessenger{};
	VkPhysicalDevice m_PhysicalDevice{};
	VkCommandPool m_CmdPool{};
	VkDevice m_Device{};
	VkSurfaceKHR m_Surface{};
	VkQueue m_GraphicsQueue{};
	VkQueue m_PresentQueue{};
	const List<CString> VALIDATION_LAYERS =
	{ "VK_LAYER_KHRONOS_validation" };
	const List<CString> DEVICE_EXTENSIONS =
	{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
public:
	explicit cVulkanDevice(const SPtr<cWindow> &window);
	virtual ~cVulkanDevice();

	inline void* GetProperty(const ecDeviceProperty& property) override
	{
		switch (property)
		{
			case ecDeviceProperty::CommandPool: return GetCommandPool();
			case ecDeviceProperty::Device: return GetDevice();
			case ecDeviceProperty::Surface: return GetSurface();
			case ecDeviceProperty::GraphicsQueue: return GetGraphicsQueue();
			case ecDeviceProperty::PresentQueue: return GetPresentQueue();
			case ecDeviceProperty::SwapchainSupportDetails: return GetSwapchainSupport();
		}
	}

private:
	void CreateGraphicsInstance();
	void SetupDebugMessenger();
	void CreateSurface();
	void ChoosePhysicalDevice();
	void CreateLogicalDevice();
	void CreateCommandPool();

	VIDECL Bool IsPhysicalDeviceSuitable(VkPhysicalDevice device);
	VIDECL List<CString> GetRequiredExtensions();
	VIDECL Bool CheckValidationLayerSupport();
	VIDECL sQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	VIDECL void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& info);
	VIDECL void HasGLFWRequiredInstanceExtensions();
	VIDECL Bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	VIDECL sSwapchainSupportDetails* QuerySwapchainSupport(VkPhysicalDevice device);
private:
	inline VkCommandPool GetCommandPool() { return m_CmdPool; }
	inline VkDevice GetDevice() { return m_Device; }
	inline VkSurfaceKHR GetSurface() { return m_Surface; }
	inline sSwapchainSupportDetails* GetSwapchainSupport() { return QuerySwapchainSupport(m_PhysicalDevice); }
	inline VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
	inline VkQueue GetPresentQueue() { return m_PresentQueue; }
};

VISRCEND

#endif //VICTORIAM_VULKANDEVICE_HPP
