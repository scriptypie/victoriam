//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_BASE_HPP
#define VICTORIAM_BASE_HPP

#include <string>
#include <vector>
#include <cstdint>

#include <Victoriam/Core/MacroDefinitions.hpp>
#include <Victoriam/Core/Memory/SmartPointers.hpp>
#include <Victoriam/Core/Memory/StandardAllocator.hpp>

VISRCBEG

VIDECL typedef char       Int8;
VIDECL typedef short      Int16;
VIDECL typedef int        Int32;
VIDECL typedef long long  Int64;

VIDECL typedef uint8_t  UInt8;
VIDECL typedef uint16_t UInt16;
VIDECL typedef uint32_t UInt32;
VIDECL typedef uint64_t UInt64;

VIDECL typedef float_t  Float32;
VIDECL typedef double_t Float64;

VIDECL typedef bool     Bool;

VIDECL typedef std::basic_string<char, std::char_traits<char>, StdAllocator<char> > String;

template<class T>
using List = std::vector<T, StdAllocator<T>>;

VISRCEND

#endif //VICTORIAM_BASE_HPP
