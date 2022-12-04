//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_AGRAPHICSCONTEXT_HPP
#define VICTORIAM_AGRAPHICSCONTEXT_HPP

#include "Victoriam/Graphics/Basics.hpp"

#include "../VulkanBackend/VulkanGraphicsContext.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL GraphicsContext {
	public:
		VIDECL static VkDevice GetDevice(const PGraphicsContext &context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetDevice();
		}

		VIDECL static VkPhysicalDevice GetPhysicalDevice(const PGraphicsContext& context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetPhysicalDevice();
		}

		VIDECL static VkPhysicalDeviceProperties GetPhysicalDeviceProperties(const PGraphicsContext& context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetPhysicalDeviceProperties();
		}

		VIDECL static VkInstance GetInstance(const PGraphicsContext& context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetInstance();
		}

		VIDECL static VkSurfaceKHR GetSurface(const PGraphicsContext &context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetSurface();
		}

		VIDECL static VkCommandPool GetCommandPool(const PGraphicsContext &context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetCommandPool();
		}

		VIDECL static SSwapchainSupportDetails GetSwapchainSupport(const PGraphicsContext &context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetSwapchainSupport();
		}

		VIDECL static VkQueue GetGraphicsQueue(const PGraphicsContext &context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetGraphicsQueue();
		}

		VIDECL static VkQueue GetPresentQueue(const PGraphicsContext &context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->GetPresentQueue();
		}
		VIDECL static SQueueFamilyIndices FindQueueFamilies(const PGraphicsContext& context) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->FindQueueFamilies(CCast<CVulkanGraphicsContext*>(context.Get())->m_PhysicalDevice);
		}
		VIDECL static void CreateBuffer(const PGraphicsContext& context, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory) {
			CCast<CVulkanGraphicsContext*>(context.Get())->CreateBuffer(size, usage, properties, buffer, bufferMemory);
		}
		VIDECL static void CopyBuffer(const PGraphicsContext& context, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
			CCast<CVulkanGraphicsContext*>(context.Get())->CopyBuffer(srcBuffer, dstBuffer, size);
		}
		VIDECL static void CopyBufferToImage(const PGraphicsContext& context, VkBuffer buffer, VkImage image, UInt32 width, UInt32 height, UInt32 layerCount) {
			CCast<CVulkanGraphicsContext*>(context.Get())->CopyBufferToImage(buffer, image, width, height, layerCount);
		}
		VIDECL static void CreateImageWithInfo(const PGraphicsContext& context, const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkDeviceSize memoryOffset, VkImage &image, VkDeviceMemory &imageMemory) {
			CCast<CVulkanGraphicsContext*>(context.Get())->CreateImageWithInfo(imageInfo, properties, memoryOffset, image, imageMemory);
		}
		VIDECL static VkFormat FindSupportedFormat(const PGraphicsContext& context, const CSet<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
			return CCast<CVulkanGraphicsContext*>(context.Get())->FindSupportedFormat(candidates, tiling, features);
		}

	};

}

VISRCEND

#endif //VICTORIAM_AGRAPHICSCONTEXT_HPP
