//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_COMPONENTBASE_HPP
#define VICTORIAM_COMPONENTBASE_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

class CGameObject;

enum class VIDECL EComponentType
{
	SComponentBase VIDECL = 0,
	SComponentRenderable VIDECL ,
	SComponentTransform VIDECL ,
	SComponentName VIDECL ,
	SComponentCamera VIDECL ,
	SComponentSun VIDECL ,
	SComponentPointLight VIDECL ,

};

#define COMPONENT_DECL(name) friend class CGameObject; VIDECL VIREQOUT inline static UInt32 GetStaticComponentID() { return CCast<UInt32>(EComponentType::S##name); } VIDECL VIREQOUT UInt32 GetComponentID() override { return GetStaticComponentID(); } VIDECL inline S##name() = default; VIDECL inline virtual ~S##name() = default;

struct VIDECL SComponentBase
{
	friend class CGameObject;
	VIDECL VIREQOUT inline static UInt32 GetStaticComponentID() { return CCast<UInt32>(EComponentType::SComponentBase); } // Root component
	VIDECL VIREQOUT virtual UInt32 GetComponentID() = 0;
public:
	VIDECL virtual ~SComponentBase() = default;
};

VISRCEND

#endif //VICTORIAM_COMPONENTBASE_HPP
