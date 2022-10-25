//
// Created by Вячеслав Кривенко on 24.10.2022.
//

#ifndef VICTORIAM_CLOG_HPP
#define VICTORIAM_CLOG_HPP

#include <iostream>

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

#ifndef NDEBUG
#define ViLog(...) printf(__VA_ARGS__)
#else
#define ViLog(...) (void)0
#endif

VISRCEND

#endif //VICTORIAM_CLOG_HPP
