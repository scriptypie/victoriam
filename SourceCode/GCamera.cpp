//
// Created by Вячеслав Кривенко on 26.10.2022.
//

#include <Victoriam/Graphics/GCamera.hpp>

VISRCBEG

SMatrix4 CCamera::GetProjection() const
{
	return m_ProjectionMat;
}

CCamera CCamera::CreateOrthographicCamera(const Float32 &left, const Float32 &right, const Float32 &top,
                                          const Float32 &bottom, const Float32 &near, const Float32 &far)
{
	SMatrix4
	projectionMatrix = glm::mat4{1.0F};
	projectionMatrix[0][0] = 2.F / (right - left);
	projectionMatrix[1][1] = 2.F / (bottom - top);
	projectionMatrix[2][2] = 1.F / (far - near);
	projectionMatrix[3][0] = -(right + left) / (right - left);
	projectionMatrix[3][1] = -(bottom + top) / (bottom - top);
	projectionMatrix[3][2] = -near / (far - near);
	return CCamera(projectionMatrix);
}

CCamera CCamera::CreatePerspectiveCamera(const Float32 &fovy, const Float32 &aspect, const Float32 &near,
                                         const Float32 &far)
{
	assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0F);
	const float tanHalfFovy = tan(fovy / 2.F);
	SMatrix4
	projectionMatrix = glm::mat4{0.0F};
	projectionMatrix[0][0] = 1.F / (aspect * tanHalfFovy);
	projectionMatrix[1][1] = 1.F / (tanHalfFovy);
	projectionMatrix[2][2] = far / (far - near);
	projectionMatrix[2][3] = 1.F;
	projectionMatrix[3][2] = -(far * near) / (far - near);
	return CCamera(projectionMatrix);
}

CCamera::CCamera() : m_ProjectionMat(SMatrix4(1.0F))
{}

VISRCEND
