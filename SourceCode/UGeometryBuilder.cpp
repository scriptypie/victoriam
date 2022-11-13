//
// Created by Вячеслав Кривенко on 30.10.2022.
//

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <tinyobjloader/TinyObjLoader.hpp>

#include <Victoriam/Utils/UGeometryBuilder.hpp>
#include <filesystem>

VISRCBEG

CGeometryBuilder& CGeometryBuilder::Get()
{
	static CGeometryBuilder instance;
	return instance;
}

SGeometryDataCreateInfo CGeometryBuilder::LoadDefaultFromFile(const String &filename)
{
	String fn = "../Resources/Assets/" + filename;
	SGeometryDataCreateInfo geometryDataCreateInfo = {};
	geometryDataCreateInfo.Vertices = DefaultVertices;
	geometryDataCreateInfo.Indices = DefaultIndices;
	InternalLoadModelFromFile(fn, geometryDataCreateInfo);
	return geometryDataCreateInfo;
}

void CGeometryBuilder::InternalLoadModelFromFile(const String &filename, SGeometryDataCreateInfo &outinfo)
{
	namespace tobj = tinyobj;
	tobj::attrib_t attrib;
	std::vector<tobj::shape_t> shapes;
	std::vector<tobj::material_t> materials;
	std::string warn, err;

	if (!tobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str()))
		ViAbort("%s\n", (warn + err).c_str());

	outinfo.Vertices.clear();
	outinfo.Indices.clear();

	CHashTable<SVertex, UInt32> uniqueVertices = {};

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			SVertex vertex = {};

			if (index.vertex_index >= 0) {
				vertex.Position = {
						attrib.vertices[3 * index.vertex_index + 0],
						attrib.vertices[3 * index.vertex_index + 1],
						attrib.vertices[3 * index.vertex_index + 2]
				};
				vertex.Color = {
						attrib.colors[3 * index.vertex_index + 0],
						attrib.colors[3 * index.vertex_index + 1],
						attrib.colors[3 * index.vertex_index + 2],
						1.0F
				};
			}

			if (index.normal_index >= 0)
				vertex.Normal = {
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2]
				};

			if (index.texcoord_index >= 0)
				vertex.UV = {
						attrib.texcoords[3 * index.texcoord_index + 0],
						attrib.texcoords[3 * index.texcoord_index + 1]
				};

			if (!uniqueVertices.count(vertex))
			{
				if (uniqueVertices.find(vertex) != uniqueVertices.end())
					uniqueVertices.at(vertex) = CCast<UInt32>(outinfo.Vertices.size());
				else
					uniqueVertices.emplace(vertex, CCast<UInt32>(outinfo.Vertices.size()));
				outinfo.Vertices.push_back(vertex);
			}
			if (uniqueVertices.find(vertex) != uniqueVertices.end())
				outinfo.Indices.push_back(uniqueVertices.at(vertex));
		}
	}

}

VISRCEND
