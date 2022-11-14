//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_CNUMERICS_HPP
#define VICTORIAM_CNUMERICS_HPP

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

VIDECL typedef char       Int8;     /* Signed integer type of 8 bits. */
VIDECL typedef short      Int16;    /* Signed integer type of 16 bits. */
VIDECL typedef int        Int32;    /* Signed integer type of 32 bits. */
VIDECL typedef long long  Int64;    /* Signed integer type of 64 bits. */

VIDECL typedef unsigned char        UInt8;      /* Unsigned integer type of 8 bits. */
VIDECL typedef unsigned short       UInt16;     /* Unsigned integer type of 16 bits. */
VIDECL typedef unsigned int         UInt32;     /* Unsigned integer type of 32 bits. */
VIDECL typedef unsigned long long   UInt64;     /* Unsigned integer type of 64 bits. */

VIDECL typedef UInt32 Signal;       /* Unsigned type that handles enum-like signals. */
VIDECL typedef UInt64 UID;          /* Unique identifier type. Long enough. */

VIDECL typedef float  Float32;    /* IEEE-754 type of 32 bits. */
VIDECL typedef double Float64;    /* IEEE-754 type of 64 bits. */

VIDECL typedef bool     Bool;       /* Unsigned integer type of 1 bit. */

VISRCEND

#endif //VICTORIAM_CNUMERICS_HPP
