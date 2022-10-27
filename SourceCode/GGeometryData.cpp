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

CGeometryData CGeometryData::Create(PDevice& device, const List<SVertex> &vertices) {
	CGeometryData data = {};
	data.m_VertexBuffer = CVertexBuffer::Create(device, vertices);
	return data;
}

CGeometryData
CGeometryData::Create(PDevice& device, const List<SVertex> &vertices, const List<UInt32> &indices) {
	CGeometryData data = {};
	data.m_VertexBuffer = CVertexBuffer::Create(device, vertices);
	data.m_IndexBuffer = CIndexBuffer::Create(device, indices);
	return data;
}

CGeometryData CGeometryData::Create(PDevice &device, const PVertexBuffer &vertexBuffer) {
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