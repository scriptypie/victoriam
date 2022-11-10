//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORPOOL_HPP
#define VICTORIAM_GDESCRIPTORPOOL_HPP

#include <Victoriam/Graphics/Structs/GDescriptorPoolCreateInfo.hpp>
#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>

VISRCBEG

/**
 * Pool of descriptors.
 * Used for allocation/freeing of new descriptor sets.
 */
class VIDECL CDescriptorPool
{
public:
	VIDECL virtual ~CDescriptorPool() = default;
	/**
	 * Allocates new descriptor set from pool, if free space is enough.
	 * @param layout Descriptor set layout
	 * @param descriptorSet Output descriptor set.
	 * @return True is successful, otherwise false.
	 */
	VIDECL VIREQOUT virtual Bool AllocateDescriptorSet(const PDescriptorSetLayout& layout, SDescriptorSet& descriptorSet) const = 0;
	/**
	 * Destroys every single one descriptor set in a list.
	 */
	VIDECL virtual void FreeDescriptorSets(List<SDescriptorSet>& descriptors) const = 0;
	/**
	 * Basically free all pool descriptors and their resources.
	 */
	VIDECL virtual void ResetPool() = 0;
	/**
	 * Creates new descriptor pool object.
	 * @param context Valid current context
	 */
	VIDECL VIREQOUT static UPtr<CDescriptorPool> Create(PGraphicsContext& context, const SDescriptorPoolCreateInfo& createInfo);
};

/**
 * DescriptorPool is like container and allocator for descriptor sets.
 */
VIDECL typedef UPtr<CDescriptorPool> PDescriptorPool;

VISRCEND

#endif //VICTORIAM_GDESCRIPTORPOOL_HPP
