//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_MSMARTPOINTERS_HPP
#define VICTORIAM_MSMARTPOINTERS_HPP

#include <Victoriam/Core/Memory/MShared.hpp>

#include <memory>

VISRCBEG

template<class T>
using SUnique = std::unique_ptr<T>;

template<class T, class ...Args>
VIDECL inline constexpr SUnique<T> FMakeUnique(Args&&...args) {
    return SUnique<T> (new T(std::forward<Args>(args)...));
}

VISRCEND

#endif //VICTORIAM_MSMARTPOINTERS_HPP
