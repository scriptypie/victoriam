//
// Created by Вячеслав Кривенко on 26.10.2022.
//

#ifndef VICTORIAM_GCAMERA_HPP
#define VICTORIAM_GCAMERA_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

class VIDECL CCamera
{
	Float32 m_Width = 1280.0F;
	Float32 m_Height = 720.0F;

	Float32 m_Sensitivity = 0.3F;
	Bool firstMouse = true;
	Float32 yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	Float32 pitch =  0.0f;
	SVector2 m_LastPos{m_Width / 2.0, m_Height / 2.0};
	Float32 m_Near, m_Far, m_Fov, m_Aspect;
	SVector3 m_Front{ 0.0F, 0.0F, -1.0F };
	SVector3 m_Up{ 0.0F, 1.0F, 0.0F };
	SMatrix4 m_Projection{ 1.0F };
	SMatrix4 m_View{1.0F};
public:
	inline CCamera() = default;
	inline ~CCamera() = default;

	VIDECL void SetViewBounds(const Float32& near, const Float32& far);
	VIDECL void SetPerspective(const Float32& fovy, const Float32& aspect);
	VIDECL void SetPerspective(const Float32& aspect);
	VIDECL void SetViewMatrix(const SMatrix4& view);
	VIDECL void SetViewportSize(const SVector2 & extent);

	VIDECL VIREQOUT Float32& Sensetivity();
	VIDECL VIREQOUT SVector3 Front() const;
	VIDECL VIREQOUT SVector3 Up() const;
	VIDECL VIREQOUT SVector3 Right() const;

	VIDECL void Update();

	VIDECL VIREQOUT SMatrix4 GetViewProjection() const;

};

VISRCEND

#endif //VICTORIAM_GCAMERA_HPP
