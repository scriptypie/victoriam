//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#ifndef VICTORIAM_GGEOMETRYDATA_HPP
#define VICTORIAM_GGEOMETRYDATA_HPP

#include <Victoriam/Graphics/GBuffer.hpp>

VISRCBEG

class VIDECL CGeometryData
{
	PBuffer m_VertexBuffer = nullptr;
	PBuffer m_IndexBuffer = nullptr;
public:
	CGeometryData() = default;
	~CGeometryData();

	VIDECL void Bind(const SCommandBuffer& buffer);
	VIDECL void Draw(const SCommandBuffer& buffer);
	VIDECL void SubmitDraw(const SCommandBuffer& buffer);

	VIDECL VIREQOUT Bool HasVertexBuffer() const;
	VIDECL VIREQOUT Bool HasIndexBuffer() const;
	VIDECL VIREQOUT Bool Empty() const;
	VIDECL void Release();

	static CGeometryData Create(PGraphicsContext& context, const List<SVertex>& vertices);
	static CGeometryData Create(PGraphicsContext& context, const List<SVertex>& vertices, const List<UInt32>& indices);
	static CGeometryData Create(const PBuffer& vertexBuffer);
	static CGeometryData Create(const PBuffer& vertexBuffer, const PBuffer& indexBuffer);
};

VISRCEND

#endif //VICTORIAM_GGEOMETRYDATA_HPP
