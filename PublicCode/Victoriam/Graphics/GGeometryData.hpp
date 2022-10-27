//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#ifndef VICTORIAM_GGEOMETRYDATA_HPP
#define VICTORIAM_GGEOMETRYDATA_HPP

#include <Victoriam/Graphics/GVertexBuffer.hpp>
#include <Victoriam/Graphics/GIndexBuffer.hpp>

VISRCBEG

class VIDECL CGeometryData
{
	PVertexBuffer m_VertexBuffer = nullptr;
	PIndexBuffer m_IndexBuffer = nullptr;
public:
	CGeometryData() = default;
	~CGeometryData();

	VIDECL void Bind(const SCommandBuffer& buffer);
	VIDECL void Draw(const SCommandBuffer& buffer);

	VIDECL VIREQOUT Bool HasVertexBuffer() const;
	VIDECL VIREQOUT Bool HasIndexBuffer() const;
	VIDECL VIREQOUT Bool Empty() const;
	VIDECL void Release();

	static CGeometryData Create(PDevice& device, const List<SVertex>& vertices);
	static CGeometryData Create(PDevice& device, const PVertexBuffer& vertexBuffer);
	static CGeometryData Create(PDevice& device, const List<SVertex>& vertices, const List<UInt32>& indices);
};

VISRCEND

#endif //VICTORIAM_GGEOMETRYDATA_HPP
