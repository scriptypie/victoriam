//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#ifndef VICTORIAM_GGEOMETRYDATA_HPP
#define VICTORIAM_GGEOMETRYDATA_HPP

#include <Victoriam/Graphics/GVertexBuffer.hpp>
#include <Victoriam/Graphics/GIndexBuffer.hpp>

VISRCBEG

/**
 * Generalization of vertex and index buffers.
 */
class VIDECL CGeometryData
{
	PVertexBuffer m_VertexBuffer = {};
	PIndexBuffer m_IndexBuffer = {};
public:
	CGeometryData() = default;
	~CGeometryData();

	VIDECL void Bind(const SCommandBuffer& buffer);
	VIDECL void Draw(const SCommandBuffer& buffer);
	VIDECL void SubmitDraw(const SCommandBuffer& buffer);

	VIDECL VIREQOUT Bool HasVertexBuffer() const;
	VIDECL VIREQOUT Bool HasIndexBuffer() const;
	VIDECL VIREQOUT Bool Empty() const;
	/**
	 * Release all resources of buffers.
	 */
	VIDECL          void Release();

	VIDECL VIREQOUT static CGeometryData Create(PGraphicsContext& context, const CList<SVertex>& vertices);
	VIDECL VIREQOUT static CGeometryData Create(PGraphicsContext& context, const CList<SVertex>& vertices, const CList<UInt32>& indices);
	VIDECL VIREQOUT static CGeometryData Create(const PVertexBuffer& vertexBuffer);
	VIDECL VIREQOUT static CGeometryData Create(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer);
};

VISRCEND

#endif //VICTORIAM_GGEOMETRYDATA_HPP
