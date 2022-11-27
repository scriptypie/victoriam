//
// Created by Вячеслав Кривенко on 06.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORWRITER_HPP
#define VICTORIAM_GDESCRIPTORWRITER_HPP

#include <Victoriam/Graphics/GDescriptorPool.hpp>

VISRCBEG

/**
 * Basic driver for simpler creating descriptor sets.
 */
class VIDECL CDescriptorWriter
{
public:
	VIDECL virtual ~CDescriptorWriter() = default;
	/**
	 * Finishes descriptor set creation.
	 * @param descriptorSet Output descriptor set.
	 * @return True if successful, otherwise false.
	 */
	VIDECL virtual Bool Build(SDescriptorSet& descriptorSet) = 0;
	VIDECL virtual void Overwrite(SDescriptorSet& descriptorSet) = 0;
	/**
	 * Creates new Descriptor writer object
	 */
	VIDECL VIREQOUT static SShared<CDescriptorWriter> Create(PDescriptorPool& pool, PDescriptorSetLayout& layout);
};

VIDECL typedef SShared<CDescriptorWriter> PDescriptorWriter;

VISRCEND

#endif //VICTORIAM_GDESCRIPTORWRITER_HPP
