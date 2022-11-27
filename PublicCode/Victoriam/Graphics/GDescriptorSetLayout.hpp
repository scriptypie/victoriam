//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORSETLAYOUT_HPP
#define VICTORIAM_GDESCRIPTORSETLAYOUT_HPP

#include <Victoriam/Graphics/Structs/GDescriptorSetLayoutCreateInfo.hpp>

VISRCBEG

/**
 * Layout object of coming descriptor set.
 */
class VIDECL CDescriptorSetLayout
{
public:
	VIDECL virtual ~CDescriptorSetLayout() = default;
	VIDECL virtual DescriptorSetBindingList& GetBindings() = 0;
	/**
	 * Creates new descriptor set layout
	 */
	VIDECL VIREQOUT static SUnique<CDescriptorSetLayout> Create(PGraphicsContext& context, const SDescriptorSetLayoutCreateInfo& createInfo);
};

VIDECL typedef SUnique<CDescriptorSetLayout> PDescriptorSetLayout;

VISRCEND

#endif //VICTORIAM_GDESCRIPTORSETLAYOUT_HPP
