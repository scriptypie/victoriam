//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <set>
#include <iostream>
#include <unordered_set>

#include "VulkanDevice.hpp"

VISRCBEG

namespace
{

	VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback
	(
			VkDebugUtilsMessageSeverityFlagBitsEXT,
			VkDebugUtilsMessageTypeFlagsEXT,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void*
	)
	{
		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	VkResult CreateDebugMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger
			)
	{
		auto func = CCast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
		if (func == nullptr)
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}

	void DestroyDebugMessengerEXT(
			VkInstance instance,
			VkDebugUtilsMessengerEXT DebugMessenger,
			const VkAllocationCallbacks* pAllocator
			)
	{
		auto func = CCast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
		if (func) func(instance, DebugMessenger, pAllocator);
	}

}

cVulkanDevice::cVulkanDevice(const SPtr<cWindow> &window)
	: m_Window(window)
{
	CreateGraphicsInstance();
	SetupDebugMessenger();
	CreateSurface();
	ChoosePhysicalDevice();
	CreateLogicalDevice();
	CreateCommandPool();
}

cVulkanDevice::~cVulkanDevice()
{
	vkDestroyCommandPool(m_Device, m_CmdPool, nullptr);
	vkDestroyDevice(m_Device, nullptr);

	if (m_EnableValidation)
		vkDestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);

	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	vkDestroyInstance(m_Instance, nullptr);
}

void cVulkanDevice::CreateGraphicsInstance()
{
	if (m_EnableValidation && !CheckValidationLayerSupport())
		throw std::runtime_error("Validation layers requested, but not available!");

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	{
		VkApplicationInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		info.pApplicationName = "VIsualEditor";
		info.pEngineName = "Victoriam Engine";
		info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		info.apiVersion = VK_VERSION_1_3;
		instanceCreateInfo.pApplicationInfo = &info;
	}
	{
		auto extensions = GetRequiredExtensions();
		instanceCreateInfo.enabledExtensionCount = CCast<UInt32>(extensions.size());
		instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
	}

}

void cVulkanDevice::SetupDebugMessenger()
{

}

void cVulkanDevice::CreateSurface()
{

}

void cVulkanDevice::ChoosePhysicalDevice()
{

}

void cVulkanDevice::CreateLogicalDevice()
{

}

void cVulkanDevice::CreateCommandPool()
{

}

Bool cVulkanDevice::IsPhysicalDeviceSuitable(VkPhysicalDevice device) {

}

List<CString> cVulkanDevice::GetRequiredExtensions() {

}

Bool cVulkanDevice::CheckValidationLayerSupport() {

}

sQueueFamilyIndices cVulkanDevice::FindQueueFamilies(VkPhysicalDevice device) {

}

void cVulkanDevice::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &info) {

}

void cVulkanDevice::HasGLFWRequiredInstanceExtensions() {

}

Bool cVulkanDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device) {

}

sSwapchainSupportDetails* cVulkanDevice::QuerySwapchainSupport(VkPhysicalDevice device) {

}

VISRCEND
