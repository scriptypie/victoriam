//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#ifndef VICTORIAM_GGEOMETRYDATA_HPP
#define VICTORIAM_GGEOMETRYDATA_HPP

#include <Victoriam/Graphics/Basics.hpp>
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
	SSphere m_BoundingSphere = {};
	SAABB m_BoundingBox = {};
	UInt64 m_Polycount = {};
public:
	CGeometryData() = default;
	~CGeometryData();

	VIDECL void Bind(const SCommandBuffer& buffer);
	VIDECL void Draw(const SCommandBuffer& buffer);
	VIDECL void SubmitDraw(const SCommandBuffer& buffer);

	VIDECL VIREQOUT Bool HasVertexBuffer() const;
	VIDECL VIREQOUT Bool HasIndexBuffer() const;
	VIDECL VIREQOUT Bool Empty() const;
	VIDECL VIREQOUT UInt64 GetPolycount() const;
	VIDECL VIREQOUT SSphere GetBoundingSphere() const;
	VIDECL VIREQOUT SAABB GetBoundingAABB() const;
	/**
	 * Release all resources of buffers.
	 */
	VIDECL          void Release();

	VIDECL VIREQOUT static CGeometryData Create(PGraphicsContext& context, const CSet<SVertex>& vertices);
	VIDECL VIREQOUT static CGeometryData Create(PGraphicsContext& context, const CSet<SVertex>& vertices, const CSet<UInt32>& indices);
	VIDECL VIREQOUT static CGeometryData Create(const PVertexBuffer& vertexBuffer);
	VIDECL VIREQOUT static CGeometryData Create(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer);
};

VISRCEND

#endif //VICTORIAM_GGEOMETRYDATA_HPP
