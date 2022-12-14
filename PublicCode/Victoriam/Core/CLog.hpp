//
// Created by Вячеслав Кривенко on 24.10.2022.
//

#ifndef VICTORIAM_CLOG_HPP
#define VICTORIAM_CLOG_HPP

#include <iostream>

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

#ifndef NDEBUG
#define ViLog(...) std::cout << __VA_ARGS__ << "\n"
#else
#define ViLog(...) (void)0
#endif

#define ViAbort(...) { ViLog(__VA_ARGS__); abort(); } (void)0

VISRCEND

#endif //VICTORIAM_CLOG_HPP
