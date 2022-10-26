//
// Created by Вячеслав Кривенко on 26.10.2022.
//

#ifndef VICTORIAM_GCAMERA_HPP
#define VICTORIAM_GCAMERA_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

class VIDECL CCamera
{
	SMatrix4 m_ProjectionMat;
	inline explicit CCamera(const SMatrix4& proj) : m_ProjectionMat(proj) {}
public:
	CCamera();
	~CCamera() = default;

	VIDECL VIREQOUT SMatrix4 GetProjection() const;

	VIDECL VIREQOUT static CCamera CreateOrthographicCamera(const Float32& left, const Float32& right, const Float32& top, const Float32& bottom, const Float32& near, const Float32& far);
	VIDECL VIREQOUT static CCamera CreatePerspectiveCamera(const Float32& fovy, const Float32& aspect, const Float32& near, const Float32& far);
};

VISRCEND

#endif //VICTORIAM_GCAMERA_HPP
