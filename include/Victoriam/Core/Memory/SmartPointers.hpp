//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_SMARTPOINTERS_HPP
#define VICTORIAM_SMARTPOINTERS_HPP

#include <memory>

#include <Victoriam/Core/MacroDefinitions.hpp>

VISRCBEG

template<class T>
using UPtr = std::unique_ptr<T>;

template<class T, class ...Args>
VIDECL inline constexpr UPtr<T> CreateUPtr(Args&&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<class T>
using SPtr = std::shared_ptr<T>;

template<class T, class ...Args>
VIDECL inline constexpr SPtr<T> CreateSPtr(Args&&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

VISRCEND

#endif //VICTORIAM_SMARTPOINTERS_HPP
