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
		VIDECL static VkDevice GetDevice(const pDevice &device) {
			return CCast<cVulkanDevice*>(device.get())->GetDevice();
		}

		VIDECL static VkSurfaceKHR GetSurface(const pDevice &device) {
			return CCast<cVulkanDevice*>(device.get())->GetSurface();
		}

		VIDECL static VkCommandPool GetCommandPool(const pDevice &device) {
			return CCast<cVulkanDevice*>(device.get())->GetCommandPool();
		}

		VIDECL static sSwapchainSupportDetails GetSwapchainSupport(const pDevice &device) {
			return CCast<cVulkanDevice*>(device.get())->GetSwapchainSupport();
		}

		VIDECL static VkQueue GetGraphicsQueue(const pDevice &device) {
			return CCast<cVulkanDevice*>(device.get())->GetGraphicsQueue();
		}

		VIDECL static VkQueue GetPresentQueue(const pDevice &device) {
			return CCast<cVulkanDevice*>(device.get())->GetPresentQueue();
		}
		VIDECL static sQueueFamilyIndices FindQueueFamilies(const pDevice& device)
		{
			return CCast<cVulkanDevice*>(device.get())->FindQueueFamilies(CCast<cVulkanDevice*>(device.get())->m_PhysicalDevice);
		}
		VIDECL static void CreateBuffer(const pDevice& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory)
		{
			CCast<cVulkanDevice*>(device.get())->CreateBuffer(size, usage, properties, buffer, bufferMemory);
		}
		VIDECL static void CopyBuffer(const pDevice& device, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
		{
			CCast<cVulkanDevice*>(device.get())->CopyBuffer(srcBuffer, dstBuffer, size);
		}
		VIDECL static void CopyBufferToImage(const pDevice& device, VkBuffer buffer, VkImage image, UInt32 width, UInt32 height, UInt32 layerCount)
		{
			CCast<cVulkanDevice*>(device.get())->CopyBufferToImage(buffer, image, width, height, layerCount);
		}
		VIDECL static void CreateImageWithInfo(const pDevice& device, const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory)
		{
			CCast<cVulkanDevice*>(device.get())->CreateImageWithInfo(imageInfo, properties, image, imageMemory);
		}
		VIDECL static VkFormat FindSupportedFormat(const pDevice& device, const List<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
		{
			return CCast<cVulkanDevice*>(device.get())->FindSupportedFormat(candidates, tiling, features);
		}

	};

}

VISRCEND

#endif //VICTORIAM_ADEVICE_HPP
