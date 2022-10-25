//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_COMPONENTBASE_HPP
#define VICTORIAM_COMPONENTBASE_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

class CGameObject;

struct VIDECL SComponentBase
{
	friend class CGameObject;
	inline static UInt32 GetStaticComponentID() { return 0; } // Root component
	virtual UInt32 GetComponentID() = 0;
public:
	virtual ~SComponentBase() = default;
};

VISRCEND

#endif //VICTORIAM_COMPONENTBASE_HPP
