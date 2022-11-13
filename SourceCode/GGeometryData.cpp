//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#include <Victoriam/Graphics/GGeometryData.hpp>

VISRCBEG

CGeometryData::~CGeometryData() {
	if (m_VertexBuffer) m_VertexBuffer.reset();
	if (m_IndexBuffer) m_IndexBuffer.reset();
}

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
CGeometryData::Create(PGraphicsContext& context, const CList<SVertex> &vertices) {
	CGeometryData data = {};
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
CGeometryData::Create(PGraphicsContext& context, const CList<SVertex> &vertices, const CList<UInt32> &indices) {
	CGeometryData data = {};
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
	return m_VertexBuffer != nullptr;
}

Bool CGeometryData::HasIndexBuffer() const {
	return m_IndexBuffer != nullptr;
}

Bool CGeometryData::Empty() const {
	return !HasVertexBuffer() || ( !HasVertexBuffer() && !HasIndexBuffer() );
}

void CGeometryData::Release() {
	if (m_IndexBuffer) m_IndexBuffer.reset();
	if (m_VertexBuffer) m_VertexBuffer.reset();
}

VISRCEND