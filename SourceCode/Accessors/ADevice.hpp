//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_ADEVICE_HPP
#define VICTORIAM_ADEVICE_HPP

#include "Victoriam/Graphics/Basics.hpp"

#include "../VulkanDevice.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL Device {
	public:
		VIDECL static VkDevice GetDevice(const PDevice &device) {
			return CCast<CVulkanDevice*>(device.get())->GetDevice();
		}

		VIDECL static VkPhysicalDevice GetPhysicalDevice(const PDevice& device) {
			return CCast<CVulkanDevice*>(device.get())->GetPhysicalDevice();
		}

		VIDECL static VkPhysicalDeviceProperties GetPhysicalDeviceProperties(const PDevice& device) {
			return CCast<CVulkanDevice*>(device.get())->GetPhysicalDeviceProperties();
		}

		VIDECL static VkInstance GetInstance(const PDevice& device) {
			return CCast<CVulkanDevice*>(device.get())->GetInstance();
		}

		VIDECL static VkSurfaceKHR GetSurface(const PDevice &device) {
			return CCast<CVulkanDevice*>(device.get())->GetSurface();
		}

		VIDECL static VkCommandPool GetCommandPool(const PDevice &device) {
			return CCast<CVulkanDevice*>(device.get())->GetCommandPool();
		}

		VIDECL static SSwapchainSupportDetails GetSwapchainSupport(const PDevice &device) {
			return CCast<CVulkanDevice*>(device.get())->GetSwapchainSupport();
		}

		VIDECL static VkQueue GetGraphicsQueue(const PDevice &device) {
			return CCast<CVulkanDevice*>(device.get())->GetGraphicsQueue();
		}

		VIDECL static VkQueue GetPresentQueue(const PDevice &device) {
			return CCast<CVulkanDevice*>(device.get())->GetPresentQueue();
		}
		VIDECL static SQueueFamilyIndices FindQueueFamilies(const PDevice& device)
		{
			return CCast<CVulkanDevice*>(device.get())->FindQueueFamilies(CCast<CVulkanDevice*>(device.get())->m_PhysicalDevice);
		}
		VIDECL static void CreateBuffer(const PDevice& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory)
		{
			CCast<CVulkanDevice*>(device.get())->CreateBuffer(size, usage, properties, buffer, bufferMemory);
		}
		VIDECL static void CopyBuffer(const PDevice& device, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
		{
			CCast<CVulkanDevice*>(device.get())->CopyBuffer(srcBuffer, dstBuffer, size);
		}
		VIDECL static void CopyBufferToImage(const PDevice& device, VkBuffer buffer, VkImage image, UInt32 width, UInt32 height, UInt32 layerCount)
		{
			CCast<CVulkanDevice*>(device.get())->CopyBufferToImage(buffer, image, width, height, layerCount);
		}
		VIDECL static void CreateImageWithInfo(const PDevice& device, const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory)
		{
			CCast<CVulkanDevice*>(device.get())->CreateImageWithInfo(imageInfo, properties, image, imageMemory);
		}
		VIDECL static VkFormat FindSupportedFormat(const PDevice& device, const List<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
		{
			return CCast<CVulkanDevice*>(device.get())->FindSupportedFormat(candidates, tiling, features);
		}

	};

}

VISRCEND

#endif //VICTORIAM_ADEVICE_HPP
