//
// Created by Вячеслав Кривенко on 26.10.2022.
//

#include <Victoriam/Graphics/GCamera.hpp>
#include <Victoriam/Input/IInput.hpp>

VISRCBEG

void CCamera::SetViewBounds(const Float32 &near, const Float32 &far) {
	m_Near = near;
	m_Far = far;
	Update();
}

void CCamera::SetPerspective(const Float32 &fovy, const Float32 &aspect) {
	m_Fov = fovy;
	m_Aspect = aspect;
	Update();
}

void CCamera::SetPerspective(const Float32 &aspect) {
	m_Aspect = aspect;
	Update();
}

SVector3 CCamera::Front() const {
	return m_Front;
}

SVector3 CCamera::Up() const {
	return m_Up;
}

SVector3 CCamera::Right() const {
	return FCross(Front(), Up());
}

SMatrix4 CCamera::GetViewProjection() const {
	return m_Projection * m_View;
}

void CCamera::Update()
{
	if (m_Aspect != Float32(m_Width / m_Height))
		m_Projection = FPerspective(m_Fov, m_Aspect, m_Near);

	SVector2 pos = CInput::GetMousePosition();

	if (firstMouse) {
		m_LastPos += pos;
		firstMouse = false;
	}

	SVector2 offset = pos - m_LastPos;
	m_LastPos = pos;

	if (CInput::IsMouseDown(EMouseCode::ButtonLeft)) {

		Float32 yawSign = Up().y < 0 ? -1.0f : 1.0f;
		yaw += (yawSign * offset.x * m_Sensitivity);
		pitch += (offset.y * m_Sensitivity);

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		m_Front.x = FCos(FRadians(yaw)) * FCos(FRadians(pitch));
		m_Front.y = FSin(FRadians(pitch));
		m_Front.z = FSin(FRadians(yaw)) * FCos(FRadians(pitch));
	}
}

void CCamera::SetViewMatrix(const SMatrix4 &view) {
	m_View = view;
}

void CCamera::SetViewportSize(const SVector2 &extent) {
	m_Width = extent.x;
	m_Height = extent.y;
	m_LastPos = { m_Width / 2.0F, m_Height / 2.0F };
}

Float32 &CCamera::Sensetivity()
{
	return m_Sensitivity;
}

void CCamera::SetFovY(const Float32 &fovy) {
	m_Fov = fovy;
}

SMatrix4 CCamera::GetView() const {
	return m_View;
}

SMatrix4 CCamera::GetProjection() const {
	return m_Projection;
}

VISRCEND
