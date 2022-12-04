//
// Created by Вячеслав Кривенко on 18.11.2022.
//

#include <Victoriam/Utils/UGeometryPacker.hpp>
#include <Victoriam/Utils/UCompression.hpp>
#include <Victoriam/IO/IOFile.hpp>

VISRCBEG

void FPackGeometryToFile(const String& filename, const SPackedGeometryInfo& info) {
	SPackedGeometryHeader packedHeader = {};
	packedHeader.NumIndices = info.Indices.Size();
	packedHeader.NumVertices = info.Vertices.Size();

	const SVertex* rawVertices = info.Vertices.Data();
	const UInt32* rawIndices = info.Indices.Data();
	const UInt64 verticesSize = sizeof(SVertex) * info.Vertices.Size();
	const UInt64 indicesSize = sizeof(UInt32) * info.Indices.Size();

	char* rawUniformVertices = CCast<char*>(rawVertices);
	char* rawUniformIndices = CCast<char*>(rawIndices);

	String containedVertices(rawUniformVertices, verticesSize);
	if (info.Vertices.Size() > 50000) {
		SCompressor::Compress(containedVertices, CompressionAlgorithmLZ4);
	}

	String containedIndices(rawUniformIndices, indicesSize);

	packedHeader.CompressedVerticesSize = containedVertices.size();
	packedHeader.CompressedIndicesSize = containedIndices.size();

	CFile file(filename, ECOpenMode::Write, ECFileFormat::Bin);
	if (file.Valid()) {
		VIGNORE file.Write(CCast<const char*>(&packedHeader), sizeof(SPackedGeometryHeader));
		VIGNORE file.Write(containedVertices);
		VIGNORE file.Write(containedIndices);
		file.Close();
	}
}

void FUnpackGeometryFromFile(const String& filename, SPackedGeometryInfo& geom) {
	SPackedGeometryHeader packedHeader = {};

	CFile file(filename, ECOpenMode::Read, ECFileFormat::Bin);
	if (file.Valid()) {
		VIGNORE file.Read(CCast<char*>(&packedHeader), sizeof(SPackedGeometryHeader));

		geom.Vertices.Resize(packedHeader.NumVertices);
		geom.Indices.Resize(packedHeader.NumIndices);

		String containedCompressedVertices(packedHeader.CompressedVerticesSize, 0);
		String containedCompressedIndices(packedHeader.CompressedIndicesSize, 0);

		VIGNORE file.Read(CCast<char*>(containedCompressedVertices.data()), packedHeader.CompressedVerticesSize);
		VIGNORE file.Read(CCast<char*>(containedCompressedIndices.data()), packedHeader.CompressedIndicesSize);
		file.Close();

		const UInt64 verticesSize = sizeof(SVertex) * geom.Vertices.Size();

		if (packedHeader.CompressedVerticesSize != verticesSize) { // we proceed decompression
			SCompressor::Decompress(containedCompressedVertices, CompressionAlgorithmLZ4, verticesSize);
		}

		void* rawVertices = geom.Vertices.Data();
		void*  rawIndices = geom.Indices.Data();

		memmove(rawVertices, CCast<void*>(containedCompressedVertices.data()), containedCompressedVertices.size());
		memmove(rawIndices, CCast<void*>(containedCompressedIndices.data()), containedCompressedIndices.size());
	}
	else {
		String error = "Error: file '" + filename + "' does not exists!";
		ViLog(error);
	}

}

VISRCEND
