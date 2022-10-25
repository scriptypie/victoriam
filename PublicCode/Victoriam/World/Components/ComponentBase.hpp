//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_COMPONENTBASE_HPP
#define VICTORIAM_COMPONENTBASE_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

class CGameObject;

enum class EComponentType
{
	SComponentBase = 0,
	SComponentRenderable,
	SComponentTransform,
	SComponentName
};

#define COMPONENT_DECL(name) friend class CGameObject; inline static UInt32 GetStaticComponentID() { return CCast<UInt32>(EComponentType::S##name); } UInt32 GetComponentID() override { return GetStaticComponentID(); }

struct VIDECL SComponentBase
{
	friend class CGameObject;
	inline static UInt32 GetStaticComponentID() { return CCast<UInt32>(EComponentType::SComponentBase); } // Root component
	virtual UInt32 GetComponentID() = 0;
public:
	virtual ~SComponentBase() = default;
};

VISRCEND

#endif //VICTORIAM_COMPONENTBASE_HPP
