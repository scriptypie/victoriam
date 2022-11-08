//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_MSMARTPOINTERS_HPP
#define VICTORIAM_MSMARTPOINTERS_HPP

#include <memory>

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

template<class T>
using UPtr = std::unique_ptr<T>;

template<class T, class ...Args>
VIDECL inline constexpr UPtr<T> CreateUPtr(Args&&...args)
{
    return UPtr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
using SPtr = std::shared_ptr<T>;

template<class T, class ...Args>
VIDECL inline constexpr SPtr<T> CreateSPtr(Args&&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

VISRCEND

#endif //VICTORIAM_MSMARTPOINTERS_HPP
