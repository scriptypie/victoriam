//
// Created by Вячеслав Кривенко on 18.11.2022.
//

#ifndef VICTORIAM_IOSTREAM_HPP
#define VICTORIAM_IOSTREAM_HPP

#include <Victoriam/Core/CNumerics.hpp>
#include <Victoriam/Core/CString.hpp>

VISRCBEG

VIDECL typedef std::ostream OStream;

class VIDECL CStream {
	StringStream buffer = {};
public:
	VIDECL inline ~CStream() = default;
	VIDECL inline  CStream() = default;
	VIDECL inline  CStream(const String& str) : buffer(str) {}
	VIDECL inline  CStream(CStream&&) noexcept = default;

	template<class T> VIDECL inline void Write(const T& v)       { buffer << v; }
	template<class T> VIDECL inline void Write(const T& v) const { buffer << v; }
	VIDECL void Clear();

	VIDECL inline String Str() const { return buffer.str(); }

	VIDECL inline explicit operator StringStream&() { return buffer; }
};

VIDECL inline constexpr StringView Newline =    {"\n"};
VIDECL inline constexpr StringView Whitespace = {" "};
VIDECL inline constexpr StringView Replace =    {"\r"};

VIDECL inline CStream& operator<<(CStream& stream, const Int8& v)       { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const UInt8& v)      { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const Int16& v)      { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const UInt16& v)     { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const Int32& v)      { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const UInt32& v)     { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const Int64& v)      { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const UInt64& v)     { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const Float32& v)    { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const Float64& v)    { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const String& v)     { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const StringView& v) { stream.Write(v); return stream; }
VIDECL inline CStream& operator<<(CStream& stream, const char* v)       { stream.Write(v); return stream; }

VISRCEND

#endif //VICTORIAM_IOSTREAM_HPP
