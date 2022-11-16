//
// Created by Вячеслав Кривенко on 16.11.2022.
//

#include "LZ4Backend.h"

#include <Victoriam/Utils/UCompression.hpp>

VISRCBEG

void SCompressor::Compress(String &buffer, const Signal &algorithm) {
	if (algorithm == CompressionAlgorithmLZ4) {
		char* out = new char[buffer.size()]{};
		auto size = CLZ4Backend::Compress(CCast<char*>(buffer.data()), out, buffer.size());
		const String newBuffer(out, size);
		delete[] out; // avoiding memory leak
		buffer = newBuffer;
	}
}

void SCompressor::Decompress(String &buffer, const Signal &algorithm, const UInt64 &originalSize) {
	if (algorithm == CompressionAlgorithmLZ4) {
		char* out = new char[originalSize]{};
		VIGNORE CLZ4Backend::Decompress(CCast<char*>(buffer.data()), out, originalSize);
		const String newBuffer(out, originalSize);
		delete[] out;
		buffer = newBuffer;
	}
}

VISRCEND
