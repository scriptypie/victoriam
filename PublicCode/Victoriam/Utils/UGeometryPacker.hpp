//
// Created by Вячеслав Кривенко on 18.11.2022.
//

#ifndef VICTORIAM_UGEOMETRYPACKER_HPP
#define VICTORIAM_UGEOMETRYPACKER_HPP

#include <Victoriam/Graphics/Structs/GGeometryDataCreateInfo.hpp>

VISRCBEG

struct VIDECL SPackedGeometryHeader {
	UInt64 NumVertices;
	UInt64 NumIndices;
	UInt64 CompressedVerticesSize;
	UInt64 CompressedIndicesSize;
};

struct VIDECL SPackedGeometryInfo {
	CSet<SVertex> Vertices;
	CSet<UInt32>  Indices;
};

VIDECL void FPackGeometryToFile(const String& filename, const SPackedGeometryInfo& info);

VIDECL void FUnpackGeometryFromFile(const String& filename, SPackedGeometryInfo& geom);

VISRCEND

#endif //VICTORIAM_UGEOMETRYPACKER_HPP
