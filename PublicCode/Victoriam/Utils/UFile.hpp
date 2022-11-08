//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_UFILE_HPP
#define VICTORIAM_UFILE_HPP

#include <fstream>

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

enum class VIDECL ECFileResult : UInt32
{
	Ok              VIDECL = 0x00000000,
	FileNotFound    VIDECL = 0x0000000F,
	NullInput       VIDECL = 0x000000F0,
};

struct VIDECL SFileTimestamp
{
	VIDECL UInt32 Second = {};
	VIDECL UInt32 Minute = {};
	VIDECL UInt32 Hour   = {};
	VIDECL UInt32 Day    = {};
	VIDECL UInt32 Month  = {};
	VIDECL UInt32 Year   = {};
};

struct VIDECL SFileView
{
	VIDECL UInt64 Size                  = {};
	VIDECL SFileTimestamp CreateDate    = {};
	VIDECL SFileTimestamp LastEditDate  = {};
	VIDECL char FirstFourBytes[4]       = {};
};

enum class VIDECL ECOpenMode : UInt32
{
	Read    VIDECL = 0x00000008,
	Write   VIDECL = 0x00000010,
};

enum class VIDECL ECFileFormat : UInt32
{
	ASCII   VIDECL = 0x00000000,
	Bin     VIDECL = 0x00000004,
};

class VIDECL CFile
{
	VIDECL String m_Filename = {};
	VIDECL std::fstream m_Handle = {};
	VIDECL Bool m_Empty = {};

public:
	VIDECL CFile(const String& filename, const ECOpenMode& omode, const ECFileFormat& fformat = ECFileFormat::ASCII);
	VIDECL CFile(const char* filename, const ECOpenMode& omode, const ECFileFormat& fformat = ECFileFormat::ASCII);
	VIDECL CFile() = default;
	VIDECL ~CFile();

	VIDECL          void Open(const String& filename, const ECOpenMode& omode, const ECFileFormat& fformat = ECFileFormat::ASCII);
	VIDECL          void Open(const char* filename, const ECOpenMode& omode, const ECFileFormat& fformat = ECFileFormat::ASCII);

	VIDECL VIREQOUT bool Valid() const;
	VIDECL VIREQOUT SFileView View();
	VIDECL VIREQOUT ECFileResult Read(String& output);
	VIDECL VIREQOUT ECFileResult Read(char* outdata, size_t sizedata);
	template<class T>
	VIDECL VIREQOUT ECFileResult Read(T& output)
	{
		SFileView view = View();
		output.resize(view.Size);
		return Read(CCast<char*>(output.data()), view.Size * sizeof(typename T::value_type));
	}
	VIDECL VIREQOUT ECFileResult Write(const String& data);
	VIDECL VIREQOUT ECFileResult Write(const char* data, const UInt64& size);
	VIDECL          void Release();
	VIDECL          void Clear();
	VIDECL          void Close();
private:
	VIDECL VIREQOUT static UInt32 ToStandardOpenMode(const ECOpenMode& omode);
	VIDECL VIREQOUT static UInt32 ToStandardFormat(const ECFileFormat& format);
};

VISRCEND

#endif //VICTORIAM_UFILE_HPP
