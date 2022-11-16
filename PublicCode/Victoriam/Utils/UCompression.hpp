//
// Created by Вячеслав Кривенко on 16.11.2022.
//

#ifndef VICTORIAM_UCOMPRESSION_HPP
#define VICTORIAM_UCOMPRESSION_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

SignalDecl CompressionAlgorithmLZ4 = 1;

struct VIDECL SCompressor {
	VIDECL static void Compress(String& buffer, const Signal& algorithm);
	VIDECL static void Decompress(String& buffer, const Signal& algorithm, const UInt64& originalSize);
};

VISRCEND

#endif //VICTORIAM_UCOMPRESSION_HPP
