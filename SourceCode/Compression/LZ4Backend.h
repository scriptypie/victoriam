//
// Created by Вячеслав Кривенко on 16.11.2022.
//

#ifndef VICTORIAM_LZ4BACKEND_H
#define VICTORIAM_LZ4BACKEND_H

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

struct VIDECL SLZ4BackendContext {
	UInt8* HashTable[0x2000];
};

/**
 * It is not real lz4 implementation, but something like 'lz4-ish'.
 */
class VIDECL CLZ4Backend {
	inline static SLZ4BackendContext ctx = {};
public:
	VIDECL VIREQOUT static UInt64 Compress(char *source, char *dest, const UInt64& inputSize);
	VIDECL VIREQOUT static UInt64 Decompress(char *source, char *dest, const UInt64& outputSize);
};
VISRCEND

#endif //VICTORIAM_LZ4BACKEND_H
