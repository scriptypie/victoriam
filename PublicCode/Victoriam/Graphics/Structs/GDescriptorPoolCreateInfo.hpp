//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORPOOLCREATEINFO_HPP
#define VICTORIAM_GDESCRIPTORPOOLCREATEINFO_HPP

#include <Victoriam/Graphics/Structs/GDescriptorSetLayoutCreateInfo.hpp>

VISRCBEG

SignalDecl DescriptorPoolCreateFreeDescriptor = 1;
SignalDecl DescriptorPoolCreateUpdateAfterBind = 2;
SignalDecl DescriptorPoolCreateHostOnly = 4;

struct VIDECL SDescriptorPoolSize
{
	VIDECL Signal DescriptorType = {};
	VIDECL UInt32 DescriptorCount = {};

	VIDECL explicit inline SDescriptorPoolSize(const Signal& type, const UInt32& count) : DescriptorType(type), DescriptorCount(count) {}
};

struct VIDECL SDescriptorPoolCreateInfo
{
	List<SDescriptorPoolSize> PoolSizeList = {};
	Signal DescriptorPoolCreateSignal = 0;
	UInt32 MaxSets = {};

	VIDECL VIREQOUT SDescriptorPoolCreateInfo& AddPoolSize(const SDescriptorPoolSize& poolSize);
	VIDECL VIREQOUT SDescriptorPoolCreateInfo& SetPoolSignal(const Signal& signal);
	VIDECL VIREQOUT SDescriptorPoolCreateInfo& SetMaxSets(const UInt32& count);

};

VISRCEND

#endif //VICTORIAM_GDESCRIPTORPOOLCREATEINFO_HPP
