//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#include <Victoriam/Graphics/GGeometryData.hpp>

VISRCBEG

CGeometryData::~CGeometryData() = default;

void CGeometryData::Bind(SCommandBuffer const &buffer) {
	m_VertexBuffer->Bind(buffer);
	if (m_IndexBuffer) m_IndexBuffer->Bind(buffer);
}

void CGeometryData::Draw(SCommandBuffer const &buffer) {
	if (m_IndexBuffer)
		m_IndexBuffer->Draw(buffer);
	else
		m_VertexBuffer->Draw(buffer);
}

void CGeometryData::SubmitDraw(SCommandBuffer const &buffer)
{
	Bind(buffer);
	Draw(buffer);
}

CGeometryData
CGeometryData::Create(PGraphicsContext& context, const CSet<SVertex> &vertices) {
	CGeometryData data = {};
	data.m_Polycount = vertices.Size() / 3;

	SVector3 minAABB = SVector3(std::numeric_limits<ScalarType>::min());
	SVector3 maxAABB = SVector3(std::numeric_limits<ScalarType>::max());

	for (auto&& vertex : vertices) {
		minAABB.x = FMin(minAABB.x, vertex.Position.x);
		minAABB.y = FMin(minAABB.y, vertex.Position.y);
		minAABB.z = FMin(minAABB.z, vertex.Position.z);

		maxAABB.x = FMax(maxAABB.x, vertex.Position.x);
		maxAABB.y = FMax(maxAABB.y, vertex.Position.y);
		maxAABB.z = FMax(maxAABB.z, vertex.Position.z);
	}
	data.m_BoundingSphere = { (maxAABB + minAABB) * 0.5F, FLength(minAABB - maxAABB) };
	data.m_BoundingBox = { minAABB, maxAABB };

	data.m_VertexBuffer = CVertexBuffer::Create(context, vertices);
	return data;
}

CGeometryData
CGeometryData::Create(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer)
{
	CGeometryData data = {};
	data.m_VertexBuffer = vertexBuffer;
	data.m_IndexBuffer = indexBuffer;
	return data;
}

CGeometryData
CGeometryData::Create(PGraphicsContext& context, const CSet<SVertex> &vertices, const CSet<UInt32> &indices) {
	CGeometryData data = {};
	data.m_Polycount = vertices.Size() / 3;

	SVector3 minAABB = SVector3(std::numeric_limits<ScalarType>::max());
	SVector3 maxAABB = SVector3(std::numeric_limits<ScalarType>::min());

	for (auto&& vertex : vertices) {
		minAABB.x = std::min(minAABB.x, vertex.Position.x);
		minAABB.y = std::min(minAABB.y, vertex.Position.y);
		minAABB.z = std::min(minAABB.z, vertex.Position.z);

		maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
		maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
		maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
	}
	data.m_BoundingSphere = { (maxAABB + minAABB), FDistance(minAABB, maxAABB) };
	data.m_BoundingBox = { minAABB, maxAABB };

	data.m_VertexBuffer = CVertexBuffer::Create(context, vertices);
	data.m_IndexBuffer = CIndexBuffer::Create(context, indices);
	return data;
}

CGeometryData
CGeometryData::Create(const PVertexBuffer &vertexBuffer) {
	CGeometryData data = {};
	data.m_VertexBuffer = vertexBuffer;
	return data;
}

Bool CGeometryData::HasVertexBuffer() const {
	return m_VertexBuffer;
}

Bool CGeometryData::HasIndexBuffer() const {
	return m_IndexBuffer;
}

Bool CGeometryData::Empty() const {
	return !HasVertexBuffer() || ( !HasVertexBuffer() && !HasIndexBuffer() );
}

void CGeometryData::Release() {
	if (m_VertexBuffer) m_VertexBuffer.Reset();
	if (m_IndexBuffer) m_IndexBuffer.Reset();
}

UInt64 CGeometryData::GetPolycount() const {
	return m_Polycount;
}

SSphere CGeometryData::GetBoundingSphere() const {
	return m_BoundingSphere;
}

SAABB CGeometryData::GetBoundingAABB() const {
	return m_BoundingBox;
}

VISRCEND