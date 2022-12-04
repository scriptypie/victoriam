//
// Created by Вячеслав Кривенко on 05.11.2022.
//

#include <Victoriam/Graphics/Structs/GDescriptorPoolCreateInfo.hpp>

VISRCBEG

SDescriptorPoolCreateInfo &SDescriptorPoolCreateInfo::AddPoolSize(const SDescriptorPoolSize &poolSize) {
	PoolSizeList.PushBack(poolSize);
	return *this;
}

SDescriptorPoolCreateInfo &SDescriptorPoolCreateInfo::SetPoolSignal(const Signal &signal) {
	DescriptorPoolCreateSignal = signal;
	return *this;
}

SDescriptorPoolCreateInfo &SDescriptorPoolCreateInfo::SetMaxSets(const UInt32 &count) {
	MaxSets = count;
	return *this;
}

VISRCEND
