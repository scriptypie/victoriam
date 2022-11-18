//
// Created by Вячеслав Кривенко on 30.10.2022.
//

#include <Victoriam/Utils/UGeometryBuilder.hpp>

#include <Victoriam/Utils/UGeometryPacker.hpp>

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
	SPackedGeometryInfo geom = {};
	FUnpackGeometryFromFile(filename, geom);
	outinfo.Vertices = FMove(geom.Vertices);
	outinfo.Indices = FMove(geom.Indices);
}

VISRCEND
