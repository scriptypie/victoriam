//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_FILE_HPP
#define VICTORIAM_FILE_HPP

#include <fstream>

#include <Victoriam/Core/Base.hpp>

VISRCBEG

enum class VIDECL ecFileResult : UInt32
{
	Ok              VIDECL = 0x00000000,
	FileNotFound    VIDECL = 0x0000000F,
	NullInput       VIDECL = 0x000000F0,
};

struct VIDECL sFileTimestamp
{
	VIDECL UInt32 Second = {};
	VIDECL UInt32 Minute = {};
	VIDECL UInt32 Hour   = {};
	VIDECL UInt32 Day    = {};
	VIDECL UInt32 Month  = {};
	VIDECL UInt32 Year   = {};
};

struct VIDECL sFileView
{
	VIDECL UInt64 Size                  = {};
	VIDECL sFileTimestamp CreateDate    = {};
	VIDECL sFileTimestamp LastEditDate  = {};
	VIDECL char FirstFourBytes[4]       = {};
};

enum class VIDECL ecOpenMode : UInt32
{
	Read    VIDECL = 0x00000008,
	Write   VIDECL = 0x00000010,
};

enum class VIDECL ecFileFormat : UInt32
{
	ASCII   VIDECL = 0x00000000,
	Bin     VIDECL = 0x00000004,
};

class VIDECL cFile
{
	VIDECL String m_Filename = {};
	VIDECL std::fstream m_Handle = {};
	VIDECL Bool m_Signal = {};

public:
	VIDECL cFile(const String& filename, const ecOpenMode& omode, const ecFileFormat& fformat = ecFileFormat::ASCII);
	VIDECL cFile(const char* filename, const ecOpenMode& omode, const ecFileFormat& fformat = ecFileFormat::ASCII);
	cFile() = default;
	~cFile();

	VIDECL void Open(const String& filename, const ecOpenMode& omode, const ecFileFormat& fformat = ecFileFormat::ASCII);
	VIDECL void Open(const char* filename, const ecOpenMode& omode, const ecFileFormat& fformat = ecFileFormat::ASCII);

	VIDECL VIREQOUT bool Valid() const;
	VIDECL VIREQOUT sFileView View();
	VIDECL VIREQOUT ecFileResult Read(String& output);
	VIDECL VIREQOUT ecFileResult Write(const String& data);
	VIDECL VIREQOUT ecFileResult Write(const char* data, const UInt64& size);
	VIDECL void Release();
	VIDECL void Clear();
	VIDECL void Close();
private:
	VIDECL VIREQOUT static UInt32 ToStandardOpenMode(const ecOpenMode& omode);
	VIDECL VIREQOUT static UInt32 ToStandardFormat(const ecFileFormat& format);
};

VISRCEND

#endif //VICTORIAM_FILE_HPP
