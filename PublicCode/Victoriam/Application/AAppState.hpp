//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AAPPSTATE_HPP
#define VICTORIAM_AAPPSTATE_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

class CAppState
{
public:
    virtual ~CAppState() = default;

    virtual void OnCreate() = 0;
    virtual void OnUpdate() = 0;
	virtual void OnUpdateGUI() = 0;
	virtual void OnDestroy() = 0;
};

using AppState = UPtr<CAppState>;

VISRCEND

#endif //VICTORIAM_AAPPSTATE_HPP
