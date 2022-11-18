//
// Created by Вячеслав Кривенко on 18.11.2022.
//

#ifndef VICTORIAM_CSTRING_HPP
#define VICTORIAM_CSTRING_HPP

#include <string>
#include <string_view>
#include <sstream>

#include <Victoriam/Core/CMacroDefinitions.hpp>
#include <Victoriam/Core/Memory/MStandardAllocator.hpp>

VISRCBEG

VIDECL typedef const char* CString; /* Simple plain C string */

VIDECL typedef std::basic_string_view<char, std::char_traits<char>> StringView;
VIDECL typedef std::basic_string<char, std::char_traits<char>, StdAllocator<char> > String;
VIDECL typedef std::basic_stringstream<char, std::char_traits<char>, StdAllocator<char> > StringStream;

VISRCEND

#endif //VICTORIAM_CSTRING_HPP
