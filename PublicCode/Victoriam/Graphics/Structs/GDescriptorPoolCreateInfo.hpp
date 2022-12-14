//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#ifndef VICTORIAM_GDESCRIPTORPOOLCREATEINFO_HPP
#define VICTORIAM_GDESCRIPTORPOOLCREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

Constant<Signal, 1> DescriptorPoolCreateFreeDescriptor;
Constant<Signal, 2> DescriptorPoolCreateUpdateAfterBind;
Constant<Signal, 4> DescriptorPoolCreateHostOnly;

/**
 * Describes what Type of descriptor we want to use, and it's size.
 */
struct VIDECL SDescriptorPoolSize {
	VIDECL Signal DescriptorType = {};
	VIDECL UInt32 DescriptorCount = {};

	VIDECL SDescriptorPoolSize() = default;
	VIDECL explicit inline SDescriptorPoolSize(const Signal& type, const UInt32& count) : DescriptorType(type), DescriptorCount(count) {}
};

/**
 * Struct that handles information for creation of descriptor pool object.
 */
struct VIDECL SDescriptorPoolCreateInfo {
	CSet<SDescriptorPoolSize> PoolSizeList = {};
	Signal DescriptorPoolCreateSignal = 0;
	UInt32 MaxSets = {};

	/**
	 * Descriptor pool may contain several types of descriptors,
	 * and we can add several of those.
	 * Usually needs to be called like this:
	 * SDescriptorPoolCreateInfo()
	 * .AddPoolSize(...)
	 * .AddPoolSize(...)
	 * ...
	 * @return Reference to SXXXCreateInfo object.
	 */
	VIDECL VIREQOUT SDescriptorPoolCreateInfo& AddPoolSize(const SDescriptorPoolSize& poolSize);
	/**
	 * Sets signal which what descriptor pool will be using for creation.
	 */
	VIDECL VIREQOUT SDescriptorPoolCreateInfo& SetPoolSignal(const Signal& signal);
	VIDECL VIREQOUT SDescriptorPoolCreateInfo& SetMaxSets(const UInt32& count);

};

VISRCEND

#endif //VICTORIAM_GDESCRIPTORPOOLCREATEINFO_HPP
