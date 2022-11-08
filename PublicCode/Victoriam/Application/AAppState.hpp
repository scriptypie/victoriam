//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AAPPSTATE_HPP
#define VICTORIAM_AAPPSTATE_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

class VIDECL CAppState
{
public:
    VIDECL virtual ~CAppState() = default;

    VIDECL virtual void OnCreate() = 0;
    VIDECL virtual void OnUpdate(const Float32& dt) = 0;
	VIDECL virtual void OnUpdateGUI() = 0;
	VIDECL virtual void OnDestroy() = 0;
};

VIDECL typedef UPtr<CAppState> PAppState;

VISRCEND

#endif //VICTORIAM_AAPPSTATE_HPP
