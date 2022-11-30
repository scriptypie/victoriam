//
// Created by Вячеслав Кривенко on 30.11.2022.
//

#include <Victoriam/Graphics/GPicture.hpp>
#include "VulkanBackend/VulkanPicture.hpp"

VISRCBEG

Bool operator==(const PPicture& a, const PPicture& b) {
	if (!a || !b) return false;
	if (a->IsHDR() != b->IsHDR()) return false;
	return  a->GetWidth() == b->GetWidth() &&
	        a->GetHeight() == b->GetHeight() &&
	        a->GetChannels() == b->GetChannels();
}

Bool operator!=(const PPicture& a, const PPicture& b) {
	return !(a == b);
}

PPicture CPicture::Create(PGraphicsContext& context, const StringView &filename) {
	return FCreateShared<CVulkanPicture>(context, filename);
}

PPicture CPicture::Create(PGraphicsContext& context, const void* data, const UInt64& size) {
	return FCreateShared<CVulkanPicture>(context, data, size);
}

VISRCEND
