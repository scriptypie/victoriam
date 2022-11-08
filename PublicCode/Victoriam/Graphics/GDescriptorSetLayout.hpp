//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORSETLAYOUT_HPP
#define VICTORIAM_GDESCRIPTORSETLAYOUT_HPP

#include <Victoriam/Graphics/Structs/GDescriptorSetLayoutCreateInfo.hpp>

VISRCBEG

class VIDECL CDescriptorSetLayout
{
public:
	VIDECL virtual ~CDescriptorSetLayout() = default;
	VIDECL virtual DescriptorSetBindingList& GetBindings() = 0;

	VIDECL VIREQOUT static UPtr<CDescriptorSetLayout> Create(PGraphicsContext& context, const SDescriptorSetLayoutCreateInfo& createInfo);
};

VIDECL typedef UPtr<CDescriptorSetLayout> PDescriptorSetLayout;

VISRCEND

#endif //VICTORIAM_GDESCRIPTORSETLAYOUT_HPP
