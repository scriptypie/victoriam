//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_APPSTATE_HPP
#define VICTORIAM_APPSTATE_HPP

#include <Victoriam/Core/Base.hpp>

VISRCBEG

class cAppState
{
public:
    virtual ~cAppState() = default;

    virtual void OnCreate() = 0;
    virtual void OnUpdate() = 0;
	virtual void OnUpdateGUI() = 0;
	virtual void OnDestroy() = 0;
};

using AppState = UPtr<cAppState>;

VISRCEND

#endif //VICTORIAM_APPSTATE_HPP
